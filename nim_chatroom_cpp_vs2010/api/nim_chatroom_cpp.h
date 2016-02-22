﻿/** @file nim_chatroom_cpp.h
  * @brief 聊天室
  * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/12/29
  */

#ifndef _NIM_CHATROOM_SDK_CPP_H_
#define _NIM_CHATROOM_SDK_CPP_H_

#include <string>
#include <functional>
#include "nim_chatroom_helper.h"

/**
* @namespace nim_chatroom
* @brief namespace nim_chatroom
*/
namespace nim_chatroom
{

#include "nim_chatroom_def.h"

/** @class ChatRoom
  * @brief 聊天室
  */
class ChatRoom
{
public:
	typedef std::function<void(__int64 room_id, const NIMChatRoomEnterStep step, int error_code, const ChatRoomInfo& info, const ChatRoomMemberInfo& my_info)>	EnterCallback;	/**< 登录回调 */
	typedef std::function<void(__int64 room_id, int error_code, NIMChatRoomExitReason exit_reason)>	ExitCallback;	/**< 登出、被踢回调 */
	typedef std::function<void(__int64 room_id, int error_code, const ChatRoomMessage& result)>	SendMsgArcCallback;	/**< 发送消息回执 */
	typedef std::function<void(__int64 room_id, const ChatRoomMessage& result)>	ReceiveMsgCallback;	/**< 接收消息回调 */
	typedef std::function<void(__int64 room_id, const ChatRoomNotification& notification)> NotificationCallback; /**< 通知回调 */
	typedef std::function<void(__int64 room_id, int error_code, const std::list<ChatRoomMemberInfo>& infos)> GetMembersCallback; /**< 在线查询成员列表回调 */
	typedef std::function<void(__int64 room_id, int error_code, const std::list<ChatRoomMessage>& msgs)> GetMsgHistoryCallback; /**< 在线查询消息历史回调 */
	typedef std::function<void(__int64 room_id, int error_code, const ChatRoomMemberInfo& info)> SetMemberAttributeCallback; /**< 设置成员身份标识回调*/
	typedef std::function<void(__int64 room_id, int error_code, const ChatRoomInfo& info)> GetChatRoomInfoCallback; /**< 获取当前聊天室信息回调*/
	typedef std::function<void(__int64 room_id, int error_code)> KickMemberCallback; /**< 踢掉指定成员回调*/
	typedef std::function<void(__int64 room_id, const NIMChatRoomLinkCondition condition)> LinkConditionCallback; /**< 服务连接情况回调*/

public:
/** @fn void RegEnterCb(const EnterCallback& cb, const std::string& json_extension = "")
  * 注册全局登录回调
  * @param[in] cb			  回调函数
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void RegEnterCb(const EnterCallback& cb, const std::string& json_extension = "");

/** @fn void RegExitCb(const ExitCallback& cb, const std::string& json_extension = "")
  * 注册全局登出、被踢回调
  * @param[in] cb			  回调函数
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void RegExitCb(const ExitCallback& cb, const std::string& json_extension = "");

/** @fn void RegSendMsgArcCb(const SendMsgArcCallback& cb, const std::string& json_extension = "")
  * 注册全局发送消息回执回调
  * @param[in] cb			  回调函数
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void RegSendMsgArcCb(const SendMsgArcCallback& cb, const std::string& json_extension = "");

/** @fn void RegReceiveMsgCb(const ReceiveMsgCallback& cb, const std::string& json_extension = "")
  * 注册全局接收消息回调
  * @param[in] cb			  回调函数
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void RegReceiveMsgCb(const ReceiveMsgCallback& cb, const std::string& json_extension = "");

/** @fn void RegNotificationCb(const NotificationCallback& cb, const std::string& json_extension = "")
  * 注册全局接收通知回调
  * @param[in] cb			  回调函数
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void RegNotificationCb(const NotificationCallback& cb, const std::string& json_extension = "");

/** @fn void RegLinkConditionCb(const LinkConditionCallback& cb, const std::string& json_extension = "")
  * 注册全局聊天室链接情况回调
  * @param[in] cb			  回调函数
  * @param[in] json_extension json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void RegLinkConditionCb(const LinkConditionCallback& cb, const std::string& json_extension = "");

/** @fn void Init(const std::string& json_extension = "")
  * 聊天室模块初始化
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return bool 模块加载结果
  */
static bool Init(const std::string& json_extension = "");

/** @fn bool Enter(const __int64 room_id, const std::string& request_login_data, const ChatRoomEnterInfo& info = ChatRoomEnterInfo(), const std::string& json_extension = "")
  * 聊天室登录
  * @param[in] room_id			  聊天室ID
  * @param[in] request_login_data 聊天室登录信息(NIM SDK请求聊天室返回的数据)
  * @param[in] info				  聊天室可选信息(暂时不支持)
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return bool 登录信息是否正确,返回失败则不会促发登录回调
  */
static bool Enter(const __int64 room_id, const std::string& request_login_data, const ChatRoomEnterInfo& info = ChatRoomEnterInfo(), const std::string& json_extension = "");

/** @fn void Exit(const __int64 room_id, const std::string& json_extension = "")
  * 聊天室登出
  * @param[in] room_id			  聊天室ID
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void Exit(const __int64 room_id, const std::string& json_extension = "");

/** @fn void Cleanup(const std::string& json_extension = "")
  * 聊天室模块清理
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void Cleanup(const std::string& json_extension = "");

/** @fn void SendMsg(const __int64 room_id, const std::string& json_msg, const std::string& json_extension = "")
  * 发送消息
  * @param[in] room_id			  聊天室ID
  * @param[in] json_msg			  消息json string(可以通过CreateTextMessage生成)
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void SendMsg(const __int64 room_id, const std::string& json_msg, const std::string& json_extension = "");

/** @fn std::string CreateTextMessage(const std::string& from_nick, const NIMChatRoomMsgType msg_type, const std::string& client_msg_id, const std::string& attach, const std::string& ext = "", bool resend = false)
  * 生成文字消息内容
  * @param[in] from_nick		昵称
  * @param[in] msg_type			消息类型
  * @param[in] client_msg_id	消息ID
  * @param[in] attach			消息内容
  * @param[in] ext				扩展字段
  * @param[in] resend			重发标记位
  * @return std::string 消息json string
  */
static std::string CreateTextMessage(const std::string& from_nick
	, const NIMChatRoomMsgType msg_type
	, const std::string& client_msg_id
	, const std::string& attach
	, const std::string& ext = ""
	, bool resend = false);

/** @fn void GetMembersOnlineAsync(const __int64 room_id, const ChatRoomGetMembersParameters &parameters, const GetMembersCallback &callback, const std::string& json_extension = "")
  * 异步查询成员列表
  * @param[in] room_id			  聊天室ID
  * @param[in] parameters		  查询参数
  * @param[in] callback			  回调函数
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void GetMembersOnlineAsync(const __int64 room_id, 
	const ChatRoomGetMembersParameters &parameters, 
	const GetMembersCallback &callback,
	const std::string& json_extension = "");

/** @fn void GetMessageHistoryOnlineAsync(const __int64 room_id, const ChatRoomGetMembersParameters &parameters, const GetMembersCallback &callback, const std::string& json_extension = "")
  * 异步查询消息历史
  * @param[in] room_id			  聊天室ID
  * @param[in] parameters		  查询参数
  * @param[in] callback			  回调函数
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void GetMessageHistoryOnlineAsync(const __int64 room_id, 
	const ChatRoomGetMsgHistoryParameters &parameters, 
	const GetMsgHistoryCallback &callback,
	const std::string& json_extension = "");

/** @fn void SetMemberAttributeOnlineAsync(const __int64 room_id, const ChatRoomSetMemberAttributeParameters &parameters, const GetMembersCallback &callback, const std::string& json_extension = "")
  * 异步设置成员身份标识
  * @param[in] room_id			  聊天室ID
  * @param[in] parameters		  查询参数
  * @param[in] callback			  回调函数
  * @param[in] json_extension	  json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void SetMemberAttributeOnlineAsync(const __int64 room_id, 
	const ChatRoomSetMemberAttributeParameters &parameters, 
	const SetMemberAttributeCallback &callback,
	const std::string& json_extension = "");

/** @fn void GetInfoAsync(const __int64 room_id, const GetChatRoomInfoCallback& callback ,const std::string &json_extension)
  * 异步获取当前聊天室信息
  * @param[in] room_id				聊天室ID
  * @param[in] callback				回调函数
  * @param[in] json_extension		json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void GetInfoAsync(const __int64 room_id, 
	const GetChatRoomInfoCallback& callback ,
	const std::string &json_extension = "");

/** @fn void GetMemberInfoByIDsAsync(const __int64 room_id, const std::list<std::string>& ids, const GetMembersCallback& callback ,const std::string &json_extension)
  * 异步获取指定成员信息
  * @param[in] room_id				聊天室ID
  * @param[in] ids					
  * @param[in] callback				回调函数
  * @param[in] json_extension		json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void GetMemberInfoByIDsAsync(const __int64 room_id, 
	const std::list<std::string>& ids, 
	const GetMembersCallback& callback,
	const std::string &json_extension = "");

/** @fn void KickMemberAsync(const __int64 room_id, const std::string& id, const std::string& notify_ext, const KickMemberCallback &callback ,const std::string &json_extension)
  * 异步踢掉指定成员
  * @param[in] room_id				聊天室ID
  * @param[in] id					成员id
  * @param[in] notify_ext			放到事件通知中的扩展字段
  * @param[in] callback				回调函数
  * @param[in] json_extension		json扩展参数（备用，目前不需要）
  * @return void 无返回值
  */
static void KickMemberAsync(const __int64 room_id, 
	const std::string& id, 
	const std::string& notify_ext, 
	const KickMemberCallback &callback, 
	const std::string &json_extension = "");
};

} 

#endif //_NIM_CHATROOM_SDK_CPP_H_