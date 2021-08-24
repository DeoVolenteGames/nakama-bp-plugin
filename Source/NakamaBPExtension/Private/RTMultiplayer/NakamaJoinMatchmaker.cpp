// Copyright 2021 DeoVolenteGames

#include "../Public/RTMultiplayer/NakamaJoinMatchmaker.h"
#include "NakamaBPExtension.h"
#include "nonstd/optional.hpp"

// https://ue4community.wiki/legacy/Creating_Asynchronous_Blueprint_Nodes

void UNakamaJoinMatchmaker::Activate()
{
	// TODO: Use FFrame::KismetExecutionMessage for logging errors?
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	};

	auto SuccessCallback = [&, this](NAKAMA_NAMESPACE::NMatchmakerTicket Ticket)
	{
		BroadcastSuccess(OnSuccess, Ticket.ticket.c_str());
	};
	auto ErrorCallback = [&, this](const NAKAMA_NAMESPACE::NRtError& Error) { BroadcastError(OnError, Error); };

	// TMap to std::map conversion
    NAKAMA_NAMESPACE::NStringMap StringProps;
	for (const auto& Pair : MatchmakingRequest.StringProperties)
	{
		StringProps[TCHAR_TO_UTF8(*Pair.Key)] = TCHAR_TO_UTF8(*Pair.Value);
	}
    NAKAMA_NAMESPACE::NStringDoubleMap NumProps;
	for (const auto& Pair : MatchmakingRequest.NumericProperties)
	{
		NumProps[TCHAR_TO_UTF8(*Pair.Key)] = Pair.Value;
	}
	
	// UE_LOG(LogNakamaBPExtension, Log, TEXT("Nakama cursor sent: %s"), TCHAR_TO_UTF8(*Cursor));
	NakamaBP::RtClient->addMatchmaker(
	    MatchmakingRequest.MinCount,
	    MatchmakingRequest.MaxCount,
	    std::string(TCHAR_TO_UTF8(*MatchmakingRequest.Query)),
	    StringProps,
	    NumProps,
		SuccessCallback,
		ErrorCallback
	);
};

UNakamaJoinMatchmaker * UNakamaJoinMatchmaker::JoinMatchmaker(const FNakamaMatchRequest MatchRequest, const FOnSuccessJoinMatchmakerResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaJoinMatchmaker* proxy = NewObject<UNakamaJoinMatchmaker>();
	proxy->MatchmakingRequest = MatchRequest;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
