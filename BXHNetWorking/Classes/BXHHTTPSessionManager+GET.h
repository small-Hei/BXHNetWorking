//
//  BXHHTTPSessionManager+GET.h
//  BXHNetWorking
//
//  Created by baishuang on 2021/1/15.
//

//#import <BXHNetWorking/BXHNetWorking.h>

#import "BXHHTTPSessionManager.h"
NS_ASSUME_NONNULL_BEGIN

@interface BXHHTTPSessionManager (GET)
/**
 *  创建GET请求
 *
 *  @param configHandler 请求配置
 *  @param downloadProgress 请求进度
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)bxh_makeGetRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
                  progress:(nullable void (^)(NSProgress * _Nonnull))downloadProgress
                   success:(nullable BXHHTTPRequestSuccessHandler)successHandler
                   failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;
@end

NS_ASSUME_NONNULL_END
