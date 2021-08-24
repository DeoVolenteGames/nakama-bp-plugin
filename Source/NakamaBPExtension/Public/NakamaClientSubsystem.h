// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaProxy.h"
#include "NakamaUnreal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RTMultiplayer/NakamaRTTypes.h"
#include "NakamaClientSubsystem.generated.h" 

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMatchedResponse, FString, Ticket, FString, MatchId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJoinedResponse, FNakamaMatch, Match);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectedResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPresenceResponse, FNakamaUserPresence, UserPresence);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMatchDataReceivedResponse, FString, MatchID, int32, OpCode, FString, Data);

/**
 * 
 */
UCLASS(Category = "Nakama BP Extension|RT Multiplayer")
class NAKAMABPEXTENSION_API UNakamaClientSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;
	
	NAKAMA_NAMESPACE::NRtDefaultClientListener RtListener;

	public:
	UPROPERTY(BlueprintAssignable);
	FOnMatchedResponse OnMatchedResponse;
	
	UPROPERTY(BlueprintAssignable);
	FOnJoinedResponse OnJoinedResponse;
	
	UPROPERTY(BlueprintAssignable);
	FOnPresenceResponse OnUserJoined;
	
	UPROPERTY(BlueprintAssignable);
	FOnPresenceResponse OnUserLeft;
	
	UPROPERTY(BlueprintAssignable);
	FOnConnectedResponse OnConnected;

	UPROPERTY(BlueprintAssignable);
	FOnMatchDataReceivedResponse OnMatchDataReceived;
};
