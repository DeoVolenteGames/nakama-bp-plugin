// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaSimpleProxy.h"
#include "NakamaStorageDelete.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension|Storage")
struct FNakamaDeleteStorageObject {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Collection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Version;

	FNakamaDeleteStorageObject() {}

	NAKAMA_NAMESPACE::NDeleteStorageObjectId ToNDeleteStorageObjectId() const
	{
		NAKAMA_NAMESPACE::NDeleteStorageObjectId DeleteObject;
		DeleteObject.collection = std::string(TCHAR_TO_UTF8(*Collection));
		DeleteObject.key = std::string(TCHAR_TO_UTF8(*Key));
		DeleteObject.version = std::string(TCHAR_TO_UTF8(*Version));
		return DeleteObject;
	}
};

/// https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#ace5743e2ec117991668ffc1491052d90
UCLASS()
class NAKAMABPEXTENSION_API UNakamaStorageDelete : public UOnlineBlueprintCallProxyBase,
	public TNakamaSimpleProxy
{
	GENERATED_BODY()

public:
	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Storage")
		static UNakamaStorageDelete* DeleteStorageObjects(const TArray<FNakamaDeleteStorageObject> ObjectIDs, const FOnSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	UPROPERTY()
	TArray<FNakamaDeleteStorageObject> ObjectIDs;

	UPROPERTY(BlueprintAssignable)
	FOnAnyResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyResponse OnError;
};
