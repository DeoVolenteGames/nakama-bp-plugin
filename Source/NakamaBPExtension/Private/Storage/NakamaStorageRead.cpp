// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Storage/NakamaStorageRead.h"
#include "NakamaBPExtension.h"

// https://wiki.unrealengine.com/Creating_Asynchronous_Blueprint_Nodes

void UNakamaStorageRead::Activate()
{
	// TODO: Use FFrame::KismetExecutionMessage for logging errors?
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	};

	auto SuccessCallback = [&, this](const NAKAMA_NAMESPACE::NStorageObjects& StorageObjects)
	{
		BroadcastSuccess(OnSuccess, MakeArray<FNakamaStorageObject>(StorageObjects));
	};
	auto ErrorCallback = [&, this](const NAKAMA_NAMESPACE::NError& Error) { BroadcastError(OnError, Error); };

	std::vector<NAKAMA_NAMESPACE::NReadStorageObjectId> ReadObjects;
	for (auto ID : ObjectIDs)
	{
		ReadObjects.push_back(ID.ToNReadStorageObjectId());
	}

	NakamaBP::Client->readStorageObjects(
		NakamaBP::Session,
		ReadObjects,
		SuccessCallback,
		ErrorCallback
	);
}


UNakamaStorageRead* UNakamaStorageRead::ReadStorageObjects(const TArray<FNakamaReadStorageObject> ObjectIDs, const FOnSuccessStorReadResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaStorageRead* proxy = NewObject<UNakamaStorageRead>();
	proxy->ObjectIDs = ObjectIDs;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
