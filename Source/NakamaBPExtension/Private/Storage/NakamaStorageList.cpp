// Copyright 2021 DeoVolenteGames

#include "../Public/Storage/NakamaStorageList.h"
#include "NakamaBPExtension.h"
#include "nonstd/optional.hpp"

// https://ue4community.wiki/legacy/Creating_Asynchronous_Blueprint_Nodes

void UNakamaStorageList::Activate()
{
	// TODO: Use FFrame::KismetExecutionMessage for logging errors?
	if (!NakamaBP::Client)
	{
		BroadcastError(OnError, TEXT("Client session not connected"));
		return;
	};

	auto SuccessCallback = [&, this](NAKAMA_NAMESPACE::NStorageObjectListPtr ObjectListPtr)
	{
		BroadcastSuccess(OnSuccess, FNakamaStorageObjectList(ObjectListPtr));
	};
	auto ErrorCallback = [&, this](const NAKAMA_NAMESPACE::NError& Error) { BroadcastError(OnError, Error); };

	// UE_LOG(LogNakamaBPExtension, Log, TEXT("Nakama cursor sent: %s"), TCHAR_TO_UTF8(*Cursor));
	NakamaBP::Client->listUsersStorageObjects(
		NakamaBP::Session,
		std::string(TCHAR_TO_UTF8(*Collection)),
		std::string(TCHAR_TO_UTF8(*UserID)),
		Limit > 0 ? optional<int>(Limit) : nullopt,
		Cursor.IsEmpty() ? nullopt : optional<std::string>(TCHAR_TO_UTF8(*Cursor)),
		SuccessCallback,
		ErrorCallback
	);
};

UNakamaStorageList * UNakamaStorageList::ListUsersStorageObjects(const FString Collection, const FString UserID, const int Limit, const FString Cursor, const FOnSuccessStorListResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate)
{
	UNakamaStorageList* proxy = NewObject<UNakamaStorageList>();
	proxy->Collection = Collection;
	proxy->UserID = UserID;
	proxy->Limit = Limit;
	proxy->Cursor = Cursor;
	proxy->OptionalSuccessFunc = SuccessDelegate;
	proxy->OptionalErrorFunc = ErrorDelegate;
	return proxy;
};
