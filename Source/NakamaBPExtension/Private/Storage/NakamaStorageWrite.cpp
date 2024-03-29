// Copyright 2021 DeoVolenteGames

#include "../Public/Storage/NakamaStorageWrite.h"
#include "NakamaBPExtension.h"
#include "nonstd/optional.hpp"

// https://ue4community.wiki/legacy/Creating_Asynchronous_Blueprint_Nodes

void UNakamaStorageWrite::Activate()
{
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	};

	auto SuccessCallback = [&, this](const NAKAMA_NAMESPACE::NStorageObjectAcks& ObjectAcks)
	{
		BroadcastSuccess(OnSuccess, NakamaBP::MakeArray<FNakamaStorageObjectAck>(ObjectAcks));
	};
	auto ErrorCallback = [&, this](const NAKAMA_NAMESPACE::NError& Error) { BroadcastError(OnError, Error); };

	std::vector<NAKAMA_NAMESPACE::NStorageObjectWrite> ObjectWrites;
	for (auto Object : Objects)
	{
		ObjectWrites.push_back(Object.ToNStorageObjectWrite());
	}

	NakamaBP::Client->writeStorageObjects(
		NakamaBP::Session,
		ObjectWrites,
		SuccessCallback,
		ErrorCallback
	);
};

UNakamaStorageWrite* UNakamaStorageWrite::WriteStorageObjects(const TArray<FNakamaWriteStorageObject> Objects, const FOnSuccessStorWriteResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaStorageWrite* proxy = NewObject<UNakamaStorageWrite>();
	proxy->Objects = Objects;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
