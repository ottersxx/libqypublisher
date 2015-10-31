//
//  QYPublisher.h
//  QYPublisher
//
//  Created by pengbin on 10/15/15.
//  Copyright © 2015 qyvideo. All rights reserved.
//
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "QYTypeDef.h"
/**
 仟壹直播推流SDK iOS版提供了iOS移动设备上的实时采集推流功能。
 本SDK提供基于x264和仟壹265等两种软件视频编码器以供选择，可以以较低的码率获得出众的视频质量。
  
 * 视频编码器提供 x264 和 qy265 两种可选项;
 * 音频编码采用AAC编码，码率可配置;
 * 支持 RTMP 协议直播推流;
 * 支持前后摄像头切换;
 * 多分辨率编码支持;
 
 ## 联系我们
 当本文档无法帮助您解决在开发中遇到的具体问题，请通过以下方式联系我们，仟壹工程师会在第一时间回复您。
 
 __E-mail__:  linsong@qyvideo.cn
 
 ## 版本信息
 __Version__: 1.0
 
 __Found__: 2015-10-15
 
 */

@interface QYPublisher : NSObject

 /**
 @abstract   rtmp主机地址
 @discussion 将音视频流推向该主机

	eg: rtmp://xxx.xxx.xxx.xxx/appname/
 */
@property (nonatomic, readonly) NSURL*      hostURL;

 /**
 @abstract   流名称
 @discussion 本次推流的名称
 推流的完整URL = hostURL/streamKey
 */
@property (nonatomic, readonly) NSString*   streamKey;

// capture settings
/**
 @abstract   视频分辨率
 @discussion 本次推流的名称

 @see QYVideoDimension
 */
@property (nonatomic, assign) QYVideoDimension          videoDimension;

/**
 @abstract   摄像头位置
 @discussion 前后摄像头
 */
@property (nonatomic, assign) AVCaptureDevicePosition   cameraPosition;

/**
 @abstract   摄像头朝向
 @discussion (1~4):down up right left
 */
@property (nonatomic, assign) AVCaptureVideoOrientation videoOrientation;

/**
 @abstract   视频帧率
 @discussion video frame per seconds 建议在[1~30]内
 */
@property (nonatomic, assign) int                       videoFPS;

// streaming settings
/**
 @abstract   视频编码器
 @discussion video codec used for encode
 @see        QYVideoCodec
 */
@property (nonatomic, assign) QYVideoCodec videoCodec;
/**
 @abstract   视频编码码率
 @discussion 视频目标编码码率, 单位为kbps
 */
@property (nonatomic, assign) int          videokBPS;   // kbit/s of video
/**
 @abstract   音频编码器
 @discussion 音频目标编码码率, 单位为kbps
 */
@property (nonatomic, assign) int          audiokBPS;   // kbit/s of audio

/**
 @abstract 当前采集设备状况
 @discussion 可以通过该属性获取采集设备的工作状况
 
 @discussion 通知：
 * QYCaptureStateDidChangeNotification 当采集设备工作状态发生变化时提供通知
 * 收到通知后，通过本属性查询新的状态，并作出相应的动作
 */
@property (nonatomic, readonly) QYCaptureState captureState;

/**
 @abstract 当前推流状况
 @discussion 可以通过该属性获取推流会话的工作状况
 
 @discussion 通知：
 * QYStreamStateDidChangeNotification 当推流工作状态发生变化时提供通知
 * 收到通知后，通过本属性查询新的状态，并作出相应的动作
 */
@property (nonatomic, readonly) QYStreamState streamState;

// Posted when capture state changes
QY_EXTERN NSString *const QYCaptureStateDidChangeNotification NS_DEPRECATED_IOS(3_2, 9_0);
// Posted when stream state changes
QY_EXTERN NSString *const QYStreamStateDidChangeNotification NS_DEPRECATED_IOS(3_2, 9_0);

// methods
/**
 @abstract 初始化方法 （step1）
 @discussion 初始化，将下列属性设置为默认值

 * _videoDimension   = QYVideoDimension_Default;
 * _cameraPosition   = AVCaptureDevicePositionBack;
 * _videoOrientation = AVCaptureVideoOrientationPortrait;
 * _videoFPS         = 15;
 * _videoCodec       = QYVideoCodec_QY265;
 * _videokBPS        = 600;
 * _audiokBPS        = 48;

 @warning QYPublisher只支持单实例推流，构造多个实例会出现异常
 */
- (instancetype) initWithDefaultCfg;

/**
 @abstract 启动预览 （step2）
 @param view 预览画面作为subview，插入到 view 的最底层
 @discussion 设置完成采集参数之后，按照设置值启动预览，启动后对采集参数修改不会生效
 @discussion 需要访问摄像头和麦克风的权限，若授权失败，其他API都会拒绝服务
 
 @warning: 开始推流前必须先启动预览
 @see videoDimension, cameraPosition, videoOrientation, videoFPS
 */
- (void) startSessionPreview: (UIView*) view;

/**
 @abstract 启动推流 （step3）
 @param      hostURL    rtmp 服务器地址 “rtmp://xxx.xxx.xxx.xxx/appname"
 @param      streamKey  本session的Stream Key
 @discussion publishURL = hostURL/streamKey 设置完成推流参数之后，将媒体流推送到 publishURL 对应的地址
 @discussion 推流参数主要是视频编码器，音视频码率的设置
 @discussion 音频采用aac编码

 @see hostURL, videoCodec,videokBPS,audiokBPS
 */
- (void) startSessionStreamTo: (NSURL*)     hostURL
                    streamKey: (NSString *) streamKey;

/**
 @abstract 停止推流 （step4）
 @discussion 断开网络连接，停止视频编码
 */
- (void) stopSessionStream;

/**
 @abstract  清理会话（step5）
 @discussion 若推流未结束，则先停止推流
 @discussion 停止采集设备

 @see stopSessionStream
 */
- (void) destroySession;

/**
 @abstract   获取当前编码的视频帧率
 @discussion 采集设备的输出帧率为videoFPS，为编码的目标帧率
 @discussion 编码的视频帧率不会高于采集帧率，但是当CPU资源不足时，编码帧率会低于采集帧率
 
 @see videoFPS
 */
- (double) encodingFPS;

/**
 @abstract   获取当前推流的码率大小
 @discussion 该码率为实际推流发出的总码率大小，包括音频和视频，单位为kbps
 
 @see videokBPS, audiokBPS
 */
- (double) streamKbps;

/**
 @abstract   切换摄像头
 @discussion 在前后摄像头间切换，从当前的摄像头切换到另一个，切换成功则修改cameraPosition的值
 @discussion 开始预览后开始有效，推流过程中也响应切换请求

 @see cameraPosition
 */
- (void) switchCamera;



@end
