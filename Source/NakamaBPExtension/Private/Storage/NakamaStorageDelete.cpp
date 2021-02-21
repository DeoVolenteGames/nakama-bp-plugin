// Copyright 2021 DeoVolenteGames

#include "../Public/Storage/NakamaStorageDelete.h"
#include "NakamaBPExtension.h"

void UNakamaStorageDelete::Activate()
{
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	};

	auto SuccessCallback = [&, this]()
	{
		BroadcastSuccess(OnSuccess);
	};
	auto ErrorCallback = [&, this](const NAKAMA_NAMESPACE::NError& Error) { BroadcastError(OnError, Error); };
	
	std::vector<NAKAMA_NAMESPACE::NDeleteStorageObjectId> DeleteObjects;
	for (auto ID : ObjectIDs)
	{
		DeleteObjects.push_back(ID.ToNDeleteStorageObjectId());
	}
	
	NakamaBP::Client->deleteStorageObjects(
		NakamaBP::Session, 
		DeleteObjects,
		SuccessCallback,
		ErrorCallback
	);
}

UNakamaStorageDelete * UNakamaStorageDelete::DeleteStorageObjects(const TArray<FNakamaDeleteStorageObject> ObjectIDs, const FOnSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaStorageDelete* proxy = NewObject<UNakamaStorageDelete>();
	proxy->ObjectIDs = ObjectIDs;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
