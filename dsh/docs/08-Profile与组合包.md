# 08 · Profile 与组合包（Bundle）

> 这一课对应官方[打包与安装插件](https://github.com/deepseek-ai/deepseek-harness/blob/main/docs/user/develop/basic/publish.zh.md)。前置：完成[插件配置](06-开发第一个插件与工具.md)。

## 1. 两个概念，两种 manifest

安装机制建立在两个概念上，二者都由一份 `package.json` 描述，但 `dsh` 键下的 manifest 种类不同：

| 概念 | 回答的问题 | 声明 | 谁写 |
| --- | --- | --- | --- |
| **组合包（Bundle）** | 这个包**贡献什么**？ | `dsh.bundle` → 一个 patch 文件 | 你编写并分发 |
| **Profile** | 这套配置**由哪些组合包按什么顺序组成**？ | `dsh.profile` → 有序 `bundles` 列表 | 用户用 `dsh --profile <name>` 启动 |

> 没有东西同时是两者。组合包是你发布的；profile 是用户启动的。

## 2. 写一个组合包

```
hello-plugin/
├── package.json       # 声明 dsh.bundle
├── cordis.patch.yml   # 被 profile 选中时应用的层
└── index.js           # patch 行引用的插件模块
```

`hello-plugin/package.json`：

```json
{
  "name": "dsh-hello-plugin",
  "version": "0.1.0",
  "type": "module",
  "main": "index.js",
  "files": ["index.js", "cordis.patch.yml"],
  "dsh": { "bundle": { "patch": "./cordis.patch.yml" } }
}
```

`hello-plugin/index.js`：

```js
export const name = 'hello-plugin'

export function apply() {
  console.log('[hello-plugin] plugin loaded!')
}
```

`hello-plugin/cordis.patch.yml`：

```yaml
- insert:
    - id: hello
      name: dsh-hello-plugin
```

- patch 是一个 patch 条目数组，与 `--patch` overlay 写法相同；区别是**按包名**引用插件（而不是相对源码路径），这样 Node 模块解析才能找到已安装的代码。
- `patch` 也接受有序文件列表，如 `["./base.patch.yml", "./web.patch.yml"]`，作为同一层按顺序应用；每个文件中的相对插件路径相对该文件解析。
- **没有 `dsh.bundle` 声明的包仍可安装，但只作为普通依赖**：`dsh plugin` 会打印警告且不激活任何层。库（供插件包 import 而非用户启用）用这种格式。

## 3. 安装进 profile

```sh
dsh plugin --profile <name> <args...>
```

它在 profile 目录内**转发给 pnpm**，所以所有 pnpm 子命令都可用。相对路径 spec（`.`、`../plugin` 及 `file:`/`link:` 形式）先锚定到**调用目录**。

从包含 `hello-plugin` 的目录安装：

```sh
dsh plugin --profile demo add ./hello-plugin
```

首次使用会初始化 profile（`@deepseek-ai/dsh-base` 作为第一个组合包），pnpm 链接该 checkout，并因该包声明了 `dsh.bundle` 而把它追加进 `dsh.profile.bundles`：

```json
{
  "name": "dsh-profile-demo",
  "private": true,
  "dependencies": { "dsh-hello-plugin": "link:/path/to/hello-plugin" },
  "dsh": {
    "profile": {
      "bundles": ["@deepseek-ai/dsh-base", "dsh-hello-plugin"]
    }
  }
}
```

验证该层（不启动）：

```sh
dsh --profile demo --dump-config   # 应出现 "# == dsh-hello-plugin" 层
dsh --profile demo
```

移除：

```sh
dsh plugin --profile demo remove dsh-hello-plugin
```

> **启动边界**：pnpm 操作成功后会改变磁盘上的 profile manifest 与组合包列表，但**正在运行的 profile 保留本次启动时的组合包集合**。添加/移除/更新组合包后要**重启该 profile**。这只是一边界；profile 或 home 里普通 `cordis.patch.yml` 的编辑通过热重载生效。

## 4. 加载顺序（决定谁能覆盖谁）

生效配置在空根之上按以下顺序逐层组合：

1. profile 的 `dsh.profile.bundles` 列表里的组合包 patch（按列表顺序，先是 `@deepseek-ai/dsh-base`，再是每个已安装组合包，按其加入顺序）
2. profile 自己的 `cordis.patch.yml`
3. home 级 `$DSH_HOME/cordis.patch.yml`
4. 每个 `--patch <path>` overlay（按 argv 顺序）

**后应用的层按行胜出**，patch 替换目标行的**整个 `config`**（不是深度合并）。两个推论：

- 你的 patch 可以按 `id` 覆盖前面层的行（就像 `dsh-web-app` 覆盖 `dsh-base` 的行），但**必须重述该行需要的每一个键**。
- 用户可以在自己 profile 的 `cordis.patch.yml` 里覆盖你的行，无需改你的包——所以优先给用户大概率会保留的默认值，其余交给 schema。

内置组合包名始终从 dsh 安装目录解析；pnpm 只管理树外的包。

## 5. 三种分发方式

### 发布到 npm（最省事，用户无需构建授权）

在 `pnpm publish` 时构建好 `lib/`，用户 `dsh plugin add your-package` 安装的是**预构建代码**：

```sh
pnpm publish --access public
# 用户：
dsh plugin --profile web add your-package
```

### 交付 tarball

```sh
pnpm pack     # 生成 your-package-0.1.0.tgz
# 用户：
dsh plugin --profile web add ./your-package-0.1.0.tgz
```

### 从 GitHub 安装（注意构建脚本这道坎）

```sh
dsh plugin --profile demo add github:you/hello-plugin
```

git 安装拉取的是**源码，不是构建产物**，没有任何环节运行你的 `build` 脚本。因此：

- **作者**要提供 `prepare` 脚本（pnpm 在 git 安装后运行它）从源码构建发布入口，且必须自包含（不能假设旁边有 monorepo checkout）。
- **用户**要为构建授权。pnpm ≥10 默认拒绝运行 git 依赖的 `prepare`，第一次 `add` 会失败；把 pnpm 打印的确切包键复制进该 profile 的 `pnpm-workspace.yaml`：

  ```yaml
  allowBuilds:
    dsh-hello-plugin: true
  ```

  然后重新 `add`。

> 把这项授权视为**允许该包代码在安装时于你机器上执行**，且不在 agent 沙箱内。只对源码可信的包授权，并锁定 commit（`github:you/hello-plugin#<sha>`）。

## 6. 版本兼容与豁免

- 点名包名的安装命令（`add`，或带 spec 的 `install`）会在 pnpm 运行**前**检查 DSH peer 依赖；**不兼容的 DSH peer 会让操作失败**，不会下载任何东西、不会运行构建脚本。
- git/tarball spec 必须先抓取，因此安装后才判定；不兼容时恢复 profile 清单与锁文件并重新安装。
- 版本豁免保存在 profile 自己的 `compatibility.json`，把精确的 `package-name@version` 映射到精确的 DSH 运行时版本列表。**插件升级和 DSH 升级都不继承授权。**

```sh
dsh plugin --profile <p> version-exemptions
dsh plugin --profile <p> allow-version <package@version> --dsh-version <runtime> --accept-risk
dsh plugin --profile <p> revoke-version <package@version> --dsh-version <runtime>
```

> 使用豁免前请**明确警告用户**不兼容插件可能导致崩溃或数据丢失，并取得对**确切插件与运行时版本**的显式许可。授权在下一次组合时生效。

## 7. 让组合包持有自己的命令行

定义了可运行应用的组合包挂载一个普通提供方插件：

```yaml
- id: hello-startup
  name: 'dsh-hello-plugin/startup'
```

该插件导出 `inject = ['cmdlineArgs']`，用 `@deepseek-ai/dsh-cmdline` 的 `parseCmdline` 调用自己的 commander program，再在 program 的 action 里把应用自有服务提供出去。启动器把自身 flag 之后的同一份不可变参数交给每个插件，因此添加应用专属 flag **无需修改启动器**，多个插件也可解析该快照。

受这些参数配置的行注入提供方服务，并在 `!!js` 选项里读取它，同时把部署取值写在旁边作为回退：

```yaml
- id: my-app
  name: '@example/my-app'
  inject: [myAppStartup]
  config:
    port: !!js ctx.myAppStartup.port ?? 8080
```

## 8. 实践清单

- [ ] 组合包 `package.json` 声明 `dsh.bundle.patch`
- [ ] patch 里**按包名**引用插件（不是相对源码路径）
- [ ] 需要与宿主共享实例的 dsh 包放在 `peerDependencies` + `devDependencies`
- [ ] 独立第三方依赖/无状态 dsh 工具包放在 `dependencies`
- [ ] 用 `dsh --profile <p> --dump-config` 验证层出现且顺序正确
- [ ] 发布后用固定版本安装验证一次
- [ ] 需要构建脚本时提供自包含 `prepare`，并在 README 说明 `allowBuilds`

## 9. 本仓库的完整示例

`dsh/examples/study-bundle/` 是一个最小但完整的组合包：注册一个工具、一个斜杠命令，附带 `package.json` / `index.js` / `cordis.patch.yml`。见其 `README.md` 的安装步骤。

下一课：[社区插件安装与使用](09-社区插件安装与使用.md)
