// Copyright 2021 DeoVolenteGames

#include "..\Public\NakamaRPC.h"
#include "NakamaBPExtension.h"

// https://ue4community.wiki/legacy/Creating_Asynchronous_Blueprint_Nodes

void UNakamaRPC::Activate()
{
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	}

	auto Success = [this](const NAKAMA_NAMESPACE::NRpc& RPC) { BroadcastSuccess(OnSuccess, FNakamaRPCResponse(RPC)); };
	auto Error = [this](const NAKAMA_NAMESPACE::NError& Error) { BroadcastError(OnError, Error); };

	NakamaBP::Client->rpc(
		NakamaBP::Session,
		std::string(TCHAR_TO_UTF8(*RpcID)),
		std::string(TCHAR_TO_UTF8(*Payload)),
		Success,
		Error);
};

UNakamaRPC * UNakamaRPC::RPC(const FString RpcID, const FString Payload, const FOnRpcSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaRPC* proxy = NewObject<UNakamaRPC>();
	proxy->RpcID = RpcID;
	proxy->Payload = Payload;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
