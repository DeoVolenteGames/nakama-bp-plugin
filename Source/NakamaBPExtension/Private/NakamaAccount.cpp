// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/NakamaAccount.h"
#include "NakamaBPExtension.h"

// https://wiki.unrealengine.com/Creating_Asynchronous_Blueprint_Nodes

void UNakamaAccount::Activate()
{
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	}

	auto SuccessCallback = [&, this](const NAKAMA_NAMESPACE::NAccount& Account) { BroadcastSuccess(OnSuccess, FNakamaAccountResponse(Account)); };
	auto ErrorCallback = [&, this](const NAKAMA_NAMESPACE::NError& Error) { BroadcastError(OnError, Error); };

	NakamaBP::Client->getAccount(
		NakamaBP::Session,
		SuccessCallback,
		ErrorCallback);
};

UNakamaAccount* UNakamaAccount::GetAccount(const FOnAccountSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaAccount* proxy = NewObject<UNakamaAccount>();
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
