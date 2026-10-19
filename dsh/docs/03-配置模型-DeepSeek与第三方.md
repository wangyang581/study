# 03 · 配置模型：DeepSeek 与第三方

> 模型变更在**下一次请求**时生效，不需要重启服务器。

## 1. 配置 DeepSeek（最简单）

打开 Web UI → **设置 → 模型**，在 DeepSeek 卡片里填入 [DeepSeek API Key](https://platform.deepseek.com/)，保存。

- 密钥是**只写**的：保存后前端只会收到脱敏描述符，永远拿不到明文。
- 密钥存储在 `$DSH_HOME/.credentials.yaml`，settings 里只保留对它的**凭据引用**。
- 模型路由立即可用。

### 用环境变量 / `.env`（适合 headless、SDK、CI）

提供方凭据按以下顺序解析：

1. 继承的环境变量
2. `$DSH_HOME/.credentials.yaml`
3. 调用目录的 `.env`
4. `$DSH_HOME/.env`

```sh
DEEPSEEK_API_KEY=sk-...
DEEPSEEK_BASE_URL=https://...   # 可选，默认公开 API
```

把变量写进 `$DSH_HOME/.env`（默认 `~/.dsh/.env`）最省事；**导出的环境变量始终优先于该文件**。注意：项目自己的 `.env` 不能设置网络代理，dsh 宁可拒绝启动也不让仓库决定流量去向。

## 2. 添加第三方提供商

选择 **添加模型提供商**，卡片默认打开**第三方模型提供商**：选取 dsh 自带的 provider（列表显示 id，例如 `anthropic`、`openai`、Kimi 的 `moonshotai`、GLM 的 `zai`），输入 API Key 保存。已安装目录会提供端点、协议和模型列表。

通过 OAuth 登录的 provider（如 Codex）暂不支持。

## 3. 添加自定义模型 API

中转站、公司网关、自建服务器或目录里没有的 provider，把卡片切到**自定义模型 API**，填：

- **Provider ID**（小写、永久，因为请求/会话/默认模型/凭据引用都用它）
- 显示名称、基础 URL、API Key
- **API 协议**：三选一
  - `openai-completions`（OpenAI Chat Completions）
  - `openai-responses`（OpenAI Responses）
  - `anthropic-messages`（Anthropic Messages）
- 至少一个模型

> 一个 provider 只使用一种协议；网关同时提供两种时建两个 provider。

### 探测模型

在**模型目录**点**获取可用模型**，可询问端点它提供哪些模型；请求用表单当前的地址/协议/密钥，响应打开可搜索勾选框，选中后点**添加所选**。保存或创建前不存储任何内容。探测只是便利手段：失败或列表为空就手动填模型 ID，效果一样。

## 4. 选择模型与推理等级

- 已配置的 provider 会出现在模型选择器中；**选择模型也会把它设为新会话默认值**。
- 已发过请求的会话保留自己日志里记录的模型。
- 声明了推理等级的模型，模型选择器会提供**推理等级**菜单；内置 provider 的模型从已安装目录继承等级。

DeepSeek 自身路由的默认推理档位在 profile patch 中设置：

```yaml
- id: llm-deepseek
  config:
    reasoningEffort: max
```

## 5. 进阶：直接编辑 profile patch

Web 设置页写入的就是 `$DSH_HOME/profiles/<profile>/cordis.patch.yml`（`dsh web` 时即 `web`）。可以直接编辑，浏览器与服务器同机时也可点设置页顶部**打开配置文件**。适配器下一次请求重新读取，无需重启。

> Cordis 配置覆盖会**替换完整条目 config**；编辑已有覆盖项时要保留其他 provider 和字段。

### 自定义 pi-ai provider 示例

```yaml
- id: llm-pi-ai
  config:
    providers:
      my-gateway:
        apiKeyEnv: GATEWAY_API_KEY
        api: openai-completions
        baseURL: https://gateway.example/v1
        models:
          - id: legacy-chat
          - id: vision-preview
            input: [text, image]
```

- `input` 接受 `text` 和 `image`，只作用于该模型；显式非空选择优先。
- 修改后想恢复继承，删除模型的 `input`/`inputModalities` 字段。
- 想让路由整体回退到图片能力，用 `defaultInput: [text, image]`（是回退值不是覆盖值）。
- 收窄内置模型请用 `modelOverrides`：

```yaml
        providers:
          anthropic:
            modelOverrides:
              claude-sonnet-4-5:
                input: [text]
```

### 推理等级（第三方）

手动录入的模型不声明任何等级，菜单里不出现。用 `reasoningEfforts` 声明，键是菜单档位，值是协议上 `reasoning_effort` 的写法：

```yaml
        reasoning: high
        models:
          - id: my-reasoner
            reasoningEfforts:
              off:
              high: high
              max: max
```

- `off` 可以留空（不传该参数）；其余档位若留空会被拒绝。
- 对「不明确关闭就会思考」的模型（如网关后面的 DeepSeek V4），设 `compat.thinkingFormat: deepseek`，让 `off` 发送 `thinking: {type: disabled}`：

```yaml
            compat:
              thinkingFormat: deepseek
            reasoningEfforts:
              off:
              high: high
              max: max
```

### 请求兼容性开关

网关密钥与地址都对，却拒绝每个请求，通常是请求形状与 OpenAI 不同。最常见两样：

- 声明推理能力的模型，系统提示词以 `role: "developer"` 发出，很多网关拒绝 → `compat.supportsDeveloperRole: false`
- 输出上限写作 `max_completion_tokens`，只认 `max_tokens` 的服务端拒绝 → `compat.maxTokensField: max_tokens`

```yaml
        providers:
          my-gateway:
            api: openai-completions
            baseURL: https://gateway.example/v1
            compat:
              supportsDeveloperRole: false
              maxTokensField: max_tokens
            models:
              - id: my-model
```

- 路由的 `compat` 是其模型的默认值，模型自身的逐字段胜出。
- 凡是写下的开关**都要给值**：`supportsDeveloperRole:`（冒号后留空）会被拒绝，因为空值会抹掉 catalog 已知信息却不给替代。
- 全部开关与所属协议见生成的 [`dsh-llm-pi-ai` 配置参考](https://github.com/deepseek-ai/deepseek-harness/blob/main/docs/config-catalog.zh.md)。

## 6. 排错速查

| 错误 | 原因 / 解法 |
| --- | --- |
| `MISSING_CREDENTIAL` | 通过模型页存密钥，或提供被引用的环境变量 |
| `UNKNOWN_MODEL` | 选已配置模型，或给自定义 provider 补模型 |
| 获取可用模型 401 | 密钥错误；模型发现调用 `GET /models` |
| 探测返回既无 `data` 也无 `models` | 端点格式不在探测范围，手动填模型 ID |
| 密钥/地址都对，网关拒绝所有请求 | 先设 `compat.supportsDeveloperRole: false` 与 `compat.maxTokensField: max_tokens` |
| 只有推理模型失败 | 同上（`developer` 角色被拒） |
| 手动模型没有推理菜单 | 给它加 `reasoningEfforts` |
| `off` 无法让 DeepSeek 停止思考 | 留空的 `off` 什么都不发；设 `compat.thinkingFormat: deepseek` |
| 图片发送前被拒绝 | 模型未声明图片模态：自定义 provider 加 `input: [text, image]` |
| compat 开关因没有值被拒 | 冒号后给值，或删掉该键以沿用 catalog 值 |

下一课：[使用 Web UI 与 CLI 模式](04-使用WebUI与CLI模式.md)
