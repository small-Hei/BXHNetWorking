//
//  BXHHTTPSessionManager+POST.h
//  BXHNetWorking
//
//  Created by baishuang on 2021/1/15.
//

#import "BXHHTTPSessionManager.h"

NS_ASSUME_NONNULL_BEGIN

@interface BXHHTTPSessionManager (POST)

/**
 *  创建POST请求
 *
 *  @param configHandler 请求配置
 *  @param cacheHandler 缓存类型回调
 *  @param downloadProgress 请求进度
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)yit_makePostRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
                      cache:(nullable BXHHTTPRequestCacheHandler)cacheHandler
                   progress:(nullable void (^)(NSProgress * _Nonnull))downloadProgress
                    success:(nullable BXHHTTPRequestSuccessHandler)successHandler
                    failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;

@end

NS_ASSUME_NONNULL_END
