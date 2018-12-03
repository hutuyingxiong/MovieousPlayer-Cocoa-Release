# MovieousPlayer-Cocoa

MovieousPlayer is a developed player researched by [movieous] (https://movieous.cn/) based on [ijkplayer] (https://github.com/bilibili/ijkplayer) . MovieousPlayer continued the Infinite stability and compatibility, In addition, it has made further optimization for the live broadcast scene, and supports the first screen open ASAP, cumulative delay optimization, DNS optimization, automatic switching of soft and hard encoding solutions, Etc., and also provides a smaller package. By integrating MovieousPlayer, developers can quickly build an excellent live broadcast and on-demand player app. MovieousPlayer SDK is a set of tools for fast and convenient development of mobile applications for viewing various media streams like RTMP, HLS, FLV, MP4, TS, and other network video formats and playback files with following formats: AVI, MOV, MKV, FLV, AVI, 3GP, 3G2, ASF, WMV, MP4, M4V, TP, TS, MTP, M2T, etc. The core of the SDK is a library for app development.

*Read this in other languages: [English](README.md), [简体中文](README.zh-cn.md).*

## Features

- [x] based on [ijkplayer](https://github.com/Bilibili/ijkplayer) ( based on [ffplay](http://ffmpeg.org/) )
- [x] HTTP, HTTPS, RTMP and HLS protocals 
- [x] Common audio and video containers (MP4, M4A, flv Etc.)
- [x] H.264 Video decoding
- [x] H.264 Hardware decoding
- [x] AAC Audio decoding
- [x] AAC Hardware decoding
- [x] Playback in backstage
- [x] First screen open in seconds
- [x] Live broadcast cumulative delay optimization
- [x] Player sound volume setting, support Mute function
- [x] Multiple-screen preview mode

## SDK Requirements

iOS 8.0 or later

## How to install
MovieousPlayer supports multiple methods for installing the library in a project.

### Installation with CocoaPods

[CocoaPods](http://cocoapods.org) is a dependency manager for Objective-C, which automates and simplifies the process of using 3rd-party libraries like MovieousPlayer in your projects. See the ["Getting Started" guide for more information](https://developer.movieous.cn/#/en-uk/iOS_Player?id=quick-start). You can install it with the following command:

```bash
$ gem install cocoapods
```

> CocoaPods 0.39.0+ is required to build MovieousPlayer.

#### Podfile

To integrate MovieousPlayer into your Xcode project using CocoaPods, specify it in your `Podfile`:

```ruby
source 'https://github.com/CocoaPods/Specs.git'
platform :ios, '8.0'

target 'TargetName' do
pod 'MovieousPlayer'
end
```

Then, run the following command:

```bash
$ pod install
```

## Instructions

The documentation: [MovieousPlayer Development Guide](https://developer.movieous.cn/#/iOS_Player) for your reference

## Description

UPlayer is  based on [ijkplayer](https://github.com/Bilibili/ijkplayer) , Thanks for [ijkplayer](https://github.com/Bilibili/ijkplayer)

## Feedback and Suggestions

Please feedback the problem by submitting issues on GitHub's repo if any problems you got, describe it as clearly as possible, It would be nice if an error message or screenshot also came together, and pointed out the type of bug or other issues in Labels.

[View existing issues and submit bugs here](https://github.com/movieous-team/Movieous-Docs/issues).
[Submit issue](https://github.com/movieous-team/MovieousPlayer-Cocoa-Release/issues/new)