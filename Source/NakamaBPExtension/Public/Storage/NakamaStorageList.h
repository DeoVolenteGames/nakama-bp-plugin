// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaStorageObject.h"
#include "NakamaStorageList.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension|Storage")
struct FNakamaStorageObjectList {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNakamaStorageObject> Objects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Cursor;

	FNakamaStorageObjectList() {}
	FNakamaStorageObjectList(NAKAMA_NAMESPACE::NStorageObjectListPtr ObjectListPtr)
	{
		Objects = TArray<FNakamaStorageObject>();
		for (const auto object : ObjectListPtr->objects)
		{
			Objects.Add(FNakamaStorageObject(object));
		}
		Cursor = FString(UTF8_TO_TCHAR(ObjectListPtr->cursor.c_str()));
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyStorListResponse, FNakamaStorageObjectList, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSuccessStorListResponse, FNakamaStorageObjectList, SuccessResponse);

/// https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#a30824ec045d4308e13d34bc285311e2a
UCLASS()
class NAKAMABPEXTENSION_API UNakamaStorageList : public UOnlineBlueprintCallProxyBase,
	public TNakamaProxy<FNakamaStorageObjectList, FOnSuccessStorListResponse, FOnAnyStorListResponse>
{
	GENERATED_BODY()

public:
	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Storage")
		static UNakamaStorageList* ListUsersStorageObjects(const FString Collection, const FString UserID, const int Limit, const FString Cursor, const FOnSuccessStorListResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	UPROPERTY()
	FString Collection;

	UPROPERTY()
	FString UserID;

	UPROPERTY()
	int Limit;

	UPROPERTY()
	FString Cursor;

	UPROPERTY(BlueprintAssignable)
	FOnAnyStorListResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyStorListResponse OnError;
};
