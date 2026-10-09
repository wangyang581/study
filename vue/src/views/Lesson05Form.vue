<script setup>
// ===================================================================
// 第 5 课：表单绑定 v-model
// v-model 是「双向绑定」的语法糖：
//   值 → 控件（把 state 显示出来）
//   控件 → 值（用户输入同步回 state）
// 底层就是 :value 绑定 + @input 监听。
// ===================================================================
import { computed, reactive, ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

// 文本类
const username = ref('')
const bio = ref('')

// 单个复选框：布尔值
const agree = ref(false)
// 多个复选框：绑定到「数组」，选中项的 value 会进入数组
const hobbies = ref([])

// 单选框：绑定到字符串
const gender = ref('female')

// 下拉：单选绑字符串，多选绑数组
const city = ref('hangzhou')
const skills = ref(['vue'])

// 修饰符
const lazyText = ref('')
const age = ref(18)
const rawInput = ref('  前后有空格  ')

// 完整表单的提交结果预览
const form = reactive({
  email: '',
  password: '',
  level: '初级',
  notify: true,
})

const preview = computed(() => ({
  username: username.value,
  bio: bio.value,
  agree: agree.value,
  hobbies: hobbies.value,
  gender: gender.value,
  city: city.value,
  skills: skills.value,
  age: age.value,
  form: { ...form },
}))

function submit() {
  alert('提交成功！\n' + JSON.stringify(preview.value, null, 2))
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 文本 / 多行文本" hint="v-model 会自动根据控件类型选择正确的绑定方式。">
    <div class="demo-row" style="align-items: flex-start; flex-direction: column; gap: 8px">
      <input v-model="username" placeholder="用户名" />
      <textarea v-model="bio" rows="3" placeholder="个人简介（textarea 直接把内容写在标签里，不要用 {{ }} 插值）" style="width: 100%" />
    </div>
    <p>用户名：<strong>{{ username || '（空）' }}</strong></p>
    <p>简介：{{ bio || '（空）' }}</p>

    <pre class="code">&lt;input v-model="username" /&gt;
&lt;textarea v-model="bio"&gt;&lt;/textarea&gt;</pre>
  </DemoCard>

  <DemoCard title="2. 复选框 checkbox" hint="单个绑定布尔值；多个绑定数组，靠 value 区分。">
    <label style="display: block; margin-bottom: 8px">
      <input v-model="agree" type="checkbox" /> 我已阅读并同意用户协议（{{ agree }}）
    </label>

    <p>选择你的爱好（{{ hobbies.length }} 个）：</p>
    <div class="demo-row">
      <label v-for="h in ['编程', '阅读', '运动', '音乐']" :key="h">
        <input v-model="hobbies" type="checkbox" :value="h" /> {{ h }}
      </label>
    </div>

    <pre class="code">&lt;!-- 单个 --&gt;
&lt;input type="checkbox" v-model="agree" /&gt;

&lt;!-- 多个：value 决定选中后往数组里放什么 --&gt;
&lt;input type="checkbox" v-model="hobbies" :value="'编程'" /&gt;</pre>
  </DemoCard>

  <DemoCard title="3. 单选框 radio 与下拉框 select" hint="radio 绑定字符串；select 单选绑字符串、多选加 multiple 并绑数组。">
    <div class="demo-row">
      <label><input v-model="gender" type="radio" value="male" /> 男</label>
      <label><input v-model="gender" type="radio" value="female" /> 女</label>
      <span class="tag">gender = {{ gender }}</span>
    </div>

    <div class="demo-row" style="margin-top: 12px">
      <label>城市：</label>
      <select v-model="city">
        <option value="beijing">北京</option>
        <option value="hangzhou">杭州</option>
        <option value="shanghai">上海</option>
        <option value="shenzhen">深圳</option>
      </select>
    </div>

    <div class="demo-row" style="margin-top: 12px">
      <label>技能（按住 Cmd/Ctrl 多选）：</label>
      <select v-model="skills" multiple size="4">
        <option value="vue">Vue</option>
        <option value="react">React</option>
        <option value="node">Node.js</option>
        <option value="css">CSS</option>
      </select>
      <span class="tag">{{ skills.join(' / ') || '未选择' }}</span>
    </div>
  </DemoCard>

  <DemoCard title="4. 修饰符 .lazy / .number / .trim" hint="处理输入时最常见的三个小需求。">
    <div class="demo-row">
      <input v-model.lazy="lazyText" placeholder=".lazy：失焦或回车才同步" />
      <span class="tag">lazyText = {{ lazyText || '（未同步）' }}</span>
    </div>

    <div class="demo-row" style="margin-top: 10px">
      <input v-model.number="age" type="number" placeholder=".number：转成数字" />
      <span class="tag">类型：{{ typeof age }}，值 {{ age }}，+1 = {{ age + 1 }}</span>
    </div>

    <div class="demo-row" style="margin-top: 10px">
      <input v-model.trim="rawInput" placeholder=".trim：自动去首尾空格" />
      <span class="tag">长度 {{ rawInput.length }}</span>
    </div>

    <pre class="code">v-model.lazy    输入时不同步，change 事件时才同步（减少更新）
v-model.number  自动把输入转成 number
v-model.trim    自动去掉首尾空格（常用于账号/搜索）</pre>
  </DemoCard>

  <DemoCard title="5. 完整表单 + 实时预览" hint="把控件和数据连起来，最后一次性提交。">
    <div class="grid-2">
      <form style="display: grid; gap: 10px" @submit.prevent="submit">
        <label>
          邮箱
          <input v-model.trim="form.email" type="email" placeholder="you@example.com" />
        </label>
        <label>
          密码
          <input v-model="form.password" type="password" placeholder="至少 6 位" />
        </label>
        <label>
          水平
          <select v-model="form.level">
            <option>初级</option>
            <option>中级</option>
            <option>高级</option>
          </select>
        </label>
        <label>
          <input v-model="form.notify" type="checkbox" /> 接收邮件通知
        </label>
        <button class="primary" type="submit">提交</button>
      </form>

      <div>
        <p class="hint">实时预览（数据驱动视图）：</p>
        <pre class="code">{{ preview }}</pre>
      </div>
    </div>

    <p class="note">
      注意：这里 <code>form.email</code> 直接用了 <code>.trim</code>，
      接口提交前仍要在后端再校验一次 —— 前端校验只是为了体验，不能当作安全边界。
    </p>
  </DemoCard>
</template>

<style scoped>
label { display: inline-flex; align-items: center; gap: 6px; font-size: 14px; }
form label { display: flex; flex-direction: column; align-items: stretch; gap: 4px; }
</style>
