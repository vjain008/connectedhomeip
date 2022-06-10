/**
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "MediaPlaybackManager.h"

using namespace std;
using namespace chip::app::DataModel;
using namespace chip::app::Clusters::MediaPlayback;
using namespace chip::Uint8;
using chip::CharSpan;

PlaybackStateEnum MediaPlaybackManager::HandleGetCurrentState()
{
    return mCurrentState;
}

uint64_t MediaPlaybackManager::HandleGetStartTime()
{
    return mStartTime;
}

uint64_t MediaPlaybackManager::HandleGetDuration()
{
    return mDuration;
}

CHIP_ERROR MediaPlaybackManager::HandleGetSampledPosition(AttributeValueEncoder & aEncoder)
{
    return aEncoder.Encode(mPlaybackPosition);
}

float MediaPlaybackManager::HandleGetPlaybackSpeed()
{
    return mPlaybackSpeed;
}

uint64_t MediaPlaybackManager::HandleGetSeekRangeStart()
{
    return mPlaybackPosition.position.Value();
}

uint64_t MediaPlaybackManager::HandleGetSeekRangeEnd()
{
    return mDuration - mPlaybackPosition.position.Value();
}

void MediaPlaybackManager::HandlePlay(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
	
	//OK key will be used to Play/Pause
    string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":13}]}}' http://127.0.0.1:9998/jsonrpc");
    ChipLogProgress(Zcl, "MediaPlaybackManager::HandlePlay command = %s", command.c_str());
    system(command.c_str());
	
    mCurrentState = PlaybackStateEnum::kPlaying;
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandlePause(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
	
	//OK key will be used to Play/Pause
    string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":13}]}}' http://127.0.0.1:9998/jsonrpc");
    ChipLogProgress(Zcl, "MediaPlaybackManager::HandlePlay command = %s", command.c_str());
    system(command.c_str());
	
    mCurrentState = PlaybackStateEnum::kPaused;
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandleStop(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
	
	//Back key will be used to Stop Video and go back to Landing screen
    string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":8}]}}' http://127.0.0.1:9998/jsonrpc");
    ChipLogProgress(Zcl, "MediaPlaybackManager::HandlePlay command = %s", command.c_str());
    system(command.c_str());
	
    mCurrentState = PlaybackStateEnum::kNotPlaying;
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandleFastForward(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
	
	//Right key will be used to FFWD Video
    string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":39}]}}' http://127.0.0.1:9998/jsonrpc");
    ChipLogProgress(Zcl, "MediaPlaybackManager::HandlePlay command = %s", command.c_str());
    system(command.c_str());
	
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandlePrevious(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
    mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(0) };
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandleRewind(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
	
	//Left key will be used to RWD Video
    string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":37}]}}' http://127.0.0.1:9998/jsonrpc");
    ChipLogProgress(Zcl, "MediaPlaybackManager::HandlePlay command = %s", command.c_str());
    system(command.c_str());
	
    mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(0) };
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandleSkipBackward(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                              const uint64_t & deltaPositionMilliseconds)
{
    // TODO: Insert code here
    uint64_t newPosition = mPlaybackPosition.position.Value() - deltaPositionMilliseconds;
    mPlaybackPosition    = { 0, chip::app::DataModel::Nullable<uint64_t>(newPosition) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandleSkipForward(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                             const uint64_t & deltaPositionMilliseconds)
{
    // TODO: Insert code here
    uint64_t newPosition = mPlaybackPosition.position.Value() + deltaPositionMilliseconds;
    newPosition          = newPosition > mDuration ? mDuration : newPosition;
    mPlaybackPosition    = { 0, chip::app::DataModel::Nullable<uint64_t>(newPosition) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandleSeek(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                      const uint64_t & positionMilliseconds)
{
    // TODO: Insert code here
    if (positionMilliseconds > mDuration)
    {
        Commands::PlaybackResponse::Type response;
        response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
        response.status = MediaPlaybackStatusEnum::kSeekOutOfRange;
        helper.Success(response);
    }
    else
    {
        mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(positionMilliseconds) };

        Commands::PlaybackResponse::Type response;
        response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
        response.status = MediaPlaybackStatusEnum::kSuccess;
        helper.Success(response);
    }
}

void MediaPlaybackManager::HandleNext(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}

void MediaPlaybackManager::HandleStartOver(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    // TODO: Insert code here
    mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(0) };
    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("data response"));
    response.status = MediaPlaybackStatusEnum::kSuccess;
    helper.Success(response);
}
