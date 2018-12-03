# MovieousPlayer-Cocoa

`Movieous 播放器 SDK` 是 [Movieous](https://movieous.cn/) 基于 [ijkplayer](https://github.com/bilibili/ijkplayer) 研发的播放器。`Movieous 播放器 SDK` 除了延续了 `ijkplayer` 良好的稳定性与兼容性之外还提供了更加简单易用的 API，另外还针对直播场景做了非常深度的优化，支持首屏秒开，累积延迟优化，DNS 优化，软硬解自动切换等等特色功能，也提供了更小的包体。通过集成 `Movieous 播放器 SDK`，开发者能够快速实现一个优秀的直播和点播播放器 app。

*其他语言版本: [English](README.md), [简体中文](README.zh-cn.md).*

## 功能

- [x] 基于 [ijkplayer](https://github.com/Bilibili/ijkplayer) ( based on [ffplay](http://ffmpeg.org/) )
- [x] HTTP、HTTPS、RTMP 和 HLS 等协议
- [x] 常见的音视频容器（MP4、M4A、flv 等）
- [x] H.264 视频解码
- [x] H.264 硬件解码
- [x] AAC 音频解码
- [x] AAC 硬件解码
- [x] 后台播放
- [x] 首屏秒开
- [x] 直播累积延时优化
- [x] 播放器音量设置，可实现静音功能
- [x] 多种画面预览模式

## 版本要求

iOS 8.0 及其以上

## 如何安装

### Cocoapods 集成

#### 安装 Cocoapods

如果您已安装 Cocoapods，则请直接跳过该步骤，直接进入下一步骤。
如果你未接触过 Cocoapods ，我们推荐您阅读 [唐巧的博客-用CocoaPods做iOS程序的依赖管理](https://blog.devtang.com/2014/05/25/use-cocoapod-to-manage-ios-lib-dependency/ "用CocoaPods做iOS程序的依赖管理") ，了解我们为何使用 Cocoapods 。另外文章中提及的淘宝源已经不再维护，需要使用 [Ruby-China RubyGems 镜像](https://gems.ruby-china.com/)替换。

如果觉得上面两个文章比较繁琐，可以直接根据我们提供的简要步骤，进行安装。
* 简要步骤：打开mac自带的 终端(terminal)，然后输入依次执行下述命令。

```bash
# 注释：Ruby-China 推荐2.6.x，实际 mac 自带的 ruby 也能用了
gem sources --add https://gems.ruby-china.com/ --remove https://rubygems.org/
gem sources -l
# 注释：上面的命令，应该会输出以下内容，>>> 代表此处为输出
>>> https://gems.ruby-china.com
# 注释：确保只有 gems.ruby-china.com

sudo gem install cocoapods
# 注释：由于我们不需要使用官方库，所以可以不执行 pod setup。
```

#### 使用Podfile集成

通过 [CocoaPods](https://cocoapods.org/) 安装可以最大化地简化安装过程。
首先，在项目根目录下的 Podfile 文件中添加以下 pods（我们假设您的项目 target 名称为 `iOSDemo`）：

```ruby
target 'iOSDemo' do
    pod 'MovieousPlayer'
end
```

<span data-type="color" style="color:rgb(51, 51, 51)"><span data-type="background" style="background-color:rgb(255, 255, 255)">然后在项目根目录执行 </span></span>`pod install`<span data-type="color" style="color:rgb(51, 51, 51)"><span data-type="background" style="background-color:rgb(255, 255, 255)"> </span></span>命令，执行成功后，SDK 就集成到项目中了。
<em>如果长时间没有拉取过pod 仓库，可能出现无法找到我们的repo的情况，此时建议先使用 </em><code><em>pod repo update</em></code><em> 更新pod仓库。</em>

## 使用方法

请参考开发者文档：[MovieousPlayer 开发指南](https://developer.movieous.cn/#/iOS_Player)

## 说明

MovieousPlayer 目前基于 [ijkplayer](https://github.com/Bilibili/ijkplayer) , 感谢 [ijkplayer](https://github.com/Bilibili/ijkplayer)

## 反馈及意见

当你遇到任何问题时，可以向我们提交 issue 来反馈。

[提交 issue](https://github.com/movieous-team/MovieousPlayer-Cocoa-Release/issues)。