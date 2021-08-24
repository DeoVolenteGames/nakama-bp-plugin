// Copyright 2021 DeoVolenteGames

#include "../Public/RTMultiplayer/NakamaJoinMatch.h"
#include "NakamaBPExtension.h"
#include "nonstd/optional.hpp"

// https://ue4community.wiki/legacy/Creating_Asynchronous_Blueprint_Nodes

void UNakamaJoinMatch::Activate()
{
	// TODO: Use FFrame::KismetExecutionMessage for logging errors?
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	};

	auto SuccessCallback = [&, this](NAKAMA_NAMESPACE::NMatch Match)
	{
		BroadcastSuccess(OnSuccess, Match);
	};
	auto ErrorCallback = [&, this](const NAKAMA_NAMESPACE::NRtError& Error) { BroadcastError(OnError, Error); };

	// TMap to std::map conversion
    NAKAMA_NAMESPACE::NStringMap StringProps;
	for (const auto& Pair : Metadata)
	{
		StringProps[TCHAR_TO_UTF8(*Pair.Key)] = TCHAR_TO_UTF8(*Pair.Value);
	}
	
	// UE_LOG(LogNakamaBPExtension, Log, TEXT("Nakama cursor sent: %s"), TCHAR_TO_UTF8(*Cursor));
	NakamaBP::RtClient->joinMatch(
	    TCHAR_TO_UTF8(*MatchID),
	    StringProps,
		SuccessCallback,
		ErrorCallback
	);
};

UNakamaJoinMatch * UNakamaJoinMatch::JoinMatch(const FString MatchID, const TMap<FString, FString> Metadata, const FOnSuccessJoinResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaJoinMatch* proxy = NewObject<UNakamaJoinMatch>();
	proxy->MatchID = MatchID;
	proxy->Metadata = Metadata;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
