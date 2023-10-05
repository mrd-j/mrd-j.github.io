<!--
 * @Author: 雪风@mud.ren
 * @Date: 2022-03-29 15:56:47
 * @LastEditTime: 2022-11-15 14:40:48
 * @LastEditors: 雪风
 * @Description:
 *  https://bbs.mud.ren
-->
## 更新日志

### 2023年6月

本次更新有不兼容调整：

- config()函数和env()函数功能分开，`env()`函数读取`/data/.env`的环境配置，而`config()`改为读取根目录下`config.json`文件配置。
- 修改CORE_CMD模块的调用函数从`exec()`改为`external_cmd()`，避免和系统efun `exec()`产生歧义。
- 增加HEADER_D，可以自动生成指定目录的头文件列表

### 2022年11月

本次更新为不兼容调整，升级需注意修改代码，主要是继承CORE_ROOM不需要再单独继承_CLEAN_UP、_DBASE和_NAME，继承CORE_AREA也不需要单独继承_NAME。

* 优化代码结构，为所有CORE_INHERIT增加_INHERIT，让功能的继承和覆盖更灵活
* 优化预加载PRELOAD，如果预加载内容为目录会自动加载目录下所有文件
* 优化VERB_D，verb指令支持放在一级目录中（以前指令必须放在二级目录下，如`verbs/std/`，现在可以直接在`verbs/`中）
* 增加声望阵营功能模块

### 2022年8月

* 增加CORE_CMD模块
* 优化http示例代码

### 2022年7月

本次更新为不兼容调整，升级需注意修改代码，如果你使用了debug这个sefun，请改名为cecho。

* 调整debug sefun输出到驱动界面
* 增加cecho sefun代替debug功能输出到玩家界面
* 调整CORE_TIME_D的set_scale()方法为可选参数，且意义发生变现，具体见源码介绍

### 2022年5月

* 增加Http客户端，优化相关示例项目
* 增加MSP接口

### 2022年3月

* 取消默认GBK编码支持
* 自定义出生点优化
* 增加谓词语法分析支持模块
* 增加部分辅助函数

### 2021年12月

* 环境增加area模式支持（移植自台湾火影MUD）
* 增加任务接口和守护进程
* 增加部分标准示例

### 2021年11月

* 调整CORE_DBSAVE函数is_ob_saved()为is_db_saved()
* 更新ansi.h，支持更多颜色和光标控制，增加示例指令colors

### 2021年9月

* 增加手机短信验证码示例接口
* 调整CONFIG_D为ENV_D，环境变量配置文件修改为`/data/.env`
* 调整sefun，itoc(int)改名为unicode(int)

### 2021年7月

* 增加CORE_INTERMUD_D，方便使用游戏列表互联，示例指令mudlists

### 2021年6月

* 优化CORE_ROOM，增加光线相关方法接口
* 增加HTTP功能示例模块（智能机器人和QQ聊天机器人）

### 2021年5月

* 增加部分sefun和默认指令
* 增加CORE_DB接口，方便数据库操作

### 2021年4月

* 增加CORE_CONFIG_D，方便游戏自定义运行配置，配置文件位置`/data/config`
* 为了数据安全调整数据库密码配置也保存在自定义配置文件中

### 2021年3月

* 调整CORE_LOGIN_D中 init_new_player 方法为`private void init_new_player(object user, object ob)`
* 新增CORE_NAME_D，用户注册校验是否重名

### 2021年1月

* MOVE 模块优化，增加可控制是否自动 look
* DBASE 模块增加默认对象设置
* ROOM 模块优化，增加函数别名
* 增加完善部分守护进程
* 更新指令系统，增加指令缓存和文件形式的别名功能(在指令目录新建 `别名.alias` 文件，内容为别名对应指令然后 rehash 即可生效)
* 更新系统自带指令使用说明，补充框架文档

### 2020年

* 发布MUDCORE测试版
