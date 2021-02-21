// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaStorageObject.h"
#include "NakamaStorageRead.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension|Storage")
struct FNakamaReadStorageObject {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Collection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserID;

	FNakamaReadStorageObject() {}

	NAKAMA_NAMESPACE::NReadStorageObjectId ToNReadStorageObjectId() const
	{
		NAKAMA_NAMESPACE::NReadStorageObjectId ReadObject;
		ReadObject.collection = std::string(TCHAR_TO_UTF8(*Collection));
		ReadObject.key = std::string(TCHAR_TO_UTF8(*Key));
		ReadObject.userId = std::string(TCHAR_TO_UTF8(*UserID));
		return ReadObject;
	}

	// FNakamaReadStorageObject(const NAccount& Account)
	// {
	// 	ID = FString(Account.user.id.c_str());
	// 	Username = FString(Account.user.username.c_str());
	// 	DisplayName = FString(Account.user.displayName.c_str());
	// 	Online = Account.user.online;
	// }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyStorReadResponse, TArray<FNakamaStorageObject>, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSuccessStorReadResponse, TArray<FNakamaStorageObject>, SuccessResponse);

/// https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#a1ead9ca384d04f84a64e9ef62efc3765
UCLASS()
class NAKAMABPEXTENSION_API UNakamaStorageRead : public UOnlineBlueprintCallProxyBase,
	public TNakamaProxy<TArray<FNakamaStorageObject>, FOnSuccessStorReadResponse, FOnAnyStorReadResponse>
{
	GENERATED_BODY()

public:
	// Generate a delegate for the OnGetResult event

	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Storage")
		static UNakamaStorageRead* ReadStorageObjects(const TArray<FNakamaReadStorageObject> ObjectIDs, const FOnSuccessStorReadResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	UPROPERTY()
	TArray<FNakamaReadStorageObject> ObjectIDs;

	UPROPERTY(BlueprintAssignable)
	FOnAnyStorReadResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyStorReadResponse OnError;
};
