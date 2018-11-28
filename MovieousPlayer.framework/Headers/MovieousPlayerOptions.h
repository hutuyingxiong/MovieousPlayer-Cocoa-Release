//
//  MovieousPlayerOptions.h
//  MovieousPlayer
//
//  Created by Chris Wang on 2018/8/14.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, MovieousPlayerDecoderType) {
    MovieousPlayerDecoderTypeSoftware,
    MovieousPlayerDecoderTypeHardware,
};

@interface MovieousPlayerOptions : NSObject

/*!
 * Indicates that this is a live streaming video, so that the MovieousPlayer will try it's best to keep low delay to the source. What need to pay attention is that turn this property on can cause more lag.
 * Default to NO
 */
@property (nonatomic, assign) BOOL liveStreaming;

/*!
 * Indicates whether Movieous Player should try to catch up with the live source, you should only enable this option when you are playing live broadcast source
 * Default to NO
 */
@property (nonatomic, assign) BOOL delayOptimization;

/*!
 * Indicates that MovieousPlayer will automatically manage AVAudioSession for you
 * Default to YES
 */
@property (nonatomic, assign) BOOL automaticallyManageAVAudioSession;

/*!
 * Indicates that MovieousPlayer will be allowed to mix audio with other app
 * Default to YES
 */
@property (nonatomic, assign) BOOL allowMixAudioWithOthers;

/*!
 * Indicates that MovieousPlayer will be allowed to mix audio with other app
 * Default to MovieousPlayerDecoderTypeHardware
 */
@property (nonatomic, assign) MovieousPlayerDecoderType decoderType;

/*!
 * Timeout interval in microsecond for network request proceeeded by MovieousPlayer
 * Default to 10 * 1000 * 1000 (10s)
 */
@property (nonatomic, assign) NSUInteger timeoutInterval;

/*!
 * Return the default option
 * @return The initialized default option
 */
+ (instancetype)defaultOptions;

@end
