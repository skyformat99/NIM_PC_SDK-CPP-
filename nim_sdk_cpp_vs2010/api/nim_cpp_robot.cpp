﻿/** @file nim_cpp_robot.cpp
  * @brief NIM SDK提供的Robot接口
  * @copyright (c) 2015-2017, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2017.06.26
  */

#include "nim_cpp_robot.h"
#include "nim_sdk_util.h"
#include "nim_json_util.h"
#include "nim_string_util.h"

namespace nim
{
#ifdef NIM_SDK_DLL_IMPORT
typedef void (*nim_robot_reg_changed_callback)(const char *json_extension, nim_robot_change_cb_func cb, const void *user_data);
typedef char* (*nim_robot_query_all_robots_block)(const char *json_extension);
typedef char* (*nim_robot_query_robot_by_accid_block)(const char *accid, const char *json_extension);
typedef void (*nim_robot_get_robots_async)(__int64 timetag, const char *json_extension, nim_robot_query_cb_func cb, const void *user_data);
#else
#include "nim_robot.h"
#endif

static void CallbackRobotInfoChange(int rescode, NIMRobotInfoChangeType type, const char *res, const char *json_extension, const void *callback)
{
	if (callback)
	{
		Robot::RobotChangedCallback* cb_pointer = (Robot::RobotChangedCallback*)callback;
		if (*cb_pointer)
		{
			RobotInfos infos;
			ParseRobotInfosStringToRobotInfos(PCharToString(res), infos);
			(*cb_pointer)((NIMResCode)rescode, type, infos);
		}
	}
}

static Robot::RobotChangedCallback* g_cb_changed_ = nullptr;
void Robot::RegChangedCallback(const RobotChangedCallback &callback, const std::string &json_extension/* = ""*/)
{
	if (g_cb_changed_)
	{
		delete g_cb_changed_;
		g_cb_changed_ = nullptr;
	}
	g_cb_changed_ = new RobotChangedCallback(callback);
	return NIM_SDK_GET_FUNC(nim_robot_reg_changed_callback)(json_extension.c_str(), &CallbackRobotInfoChange, g_cb_changed_);
}

RobotInfos Robot::QueryAllRobotInfosBlock(const std::string &json_extension/* = ""*/)
{
	char *res = NIM_SDK_GET_FUNC(nim_robot_query_all_robots_block)(json_extension.c_str());
	RobotInfos infos;
	ParseRobotInfosStringToRobotInfos(PCharToString(res), infos);
	return infos;
}

RobotInfo Robot::QueryRobotInfoByAccidBlock(const std::string &accid, const std::string &json_extension/* = ""*/)
{
	char *res = NIM_SDK_GET_FUNC(nim_robot_query_robot_by_accid_block)(accid.c_str(), json_extension.c_str());
	RobotInfo info;
	ParseRobotInfoStringToRobotInfo(PCharToString(res), info);
	return info;
}

static void CallbackRobotQuery(int rescode, const char *res, const char *json_extension, const void *callback)
{
	if (callback)
	{
		Robot::RobotQueryCallback* cb_pointer = (Robot::RobotQueryCallback*)callback;
		if (*cb_pointer)
		{
			RobotInfos infos;
			ParseRobotInfosStringToRobotInfos(PCharToString(res), infos);
			(*cb_pointer)((NIMResCode)rescode, infos);
		}
		delete cb_pointer;
	}
}

void Robot::GetRobotInfoAsync(const __int64 timetag, const RobotQueryCallback &callback, const std::string &json_extension/* = ""*/)
{
	RobotQueryCallback* cb_pointer = nullptr;
	if (callback)
	{
		cb_pointer = new RobotQueryCallback(callback);
	}
	NIM_SDK_GET_FUNC(nim_robot_get_robots_async)(timetag, json_extension.c_str(), &CallbackRobotQuery, cb_pointer);
}
}