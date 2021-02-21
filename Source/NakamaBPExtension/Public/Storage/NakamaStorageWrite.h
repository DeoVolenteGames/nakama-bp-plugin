// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaStorageWrite.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension|Storage")
struct FNakamaWriteStorageObject {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Collection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Version;

	FNakamaWriteStorageObject() {}//: Collection(""), Key(""), Value(""), Version("") {}

// 	UFUNCTION(BlueprintPure)
	NAKAMA_NAMESPACE::NStorageObjectWrite ToNStorageObjectWrite() const
	{
		auto WriteObject = NAKAMA_NAMESPACE::NStorageObjectWrite();
		WriteObject.collection = std::string(TCHAR_TO_UTF8(*Collection));
		WriteObject.key = std::string(TCHAR_TO_UTF8(*Key));
		WriteObject.value = std::string(TCHAR_TO_UTF8(*Value));
		WriteObject.version = std::string(TCHAR_TO_UTF8(*Version));
		return WriteObject;
	}
};

USTRUCT(BlueprintType, Category = "Nakama BP Extension|Storage")
struct FNakamaStorageObjectAck {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Collection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	FNakamaStorageObjectAck() {}
	FNakamaStorageObjectAck(NAKAMA_NAMESPACE::NStorageObjectAck ObjectAck)
	{
		Collection = FString(ObjectAck.collection.c_str());
		Key = FString(ObjectAck.key.c_str());
		UserID = FString(ObjectAck.userId.c_str());
		Version = FString(ObjectAck.version.c_str());
	}

	static TArray<FNakamaStorageObjectAck> MakeArray(const NAKAMA_NAMESPACE::NStorageObjectAcks& Vector)
	{
		TArray<FNakamaStorageObjectAck> Array;
		Array.SetNumUninitialized(Vector.size());
 
		for(int i=0; i< Vector.size(); i++){
			Array[i] = Vector[i];
		}

		return Array;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyStorWriteResponse, TArray<FNakamaStorageObjectAck>, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSuccessStorWriteResponse, TArray<FNakamaStorageObjectAck>, SuccessResponse);

/// https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#a0bf0d83328a658975f8c20472023b1be
UCLASS()
class NAKAMABPEXTENSION_API UNakamaStorageWrite : public UOnlineBlueprintCallProxyBase,
	public TNakamaProxy<TArray<FNakamaStorageObjectAck>, FOnSuccessStorWriteResponse, FOnAnyStorWriteResponse>
{
	GENERATED_BODY()

public:
	// Generate a delegate for the OnGetResult event

	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Storage")
		static UNakamaStorageWrite* WriteStorageObjects(const TArray<FNakamaWriteStorageObject> Objects, const FOnSuccessStorWriteResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	UPROPERTY()
	TArray<FNakamaWriteStorageObject> Objects;

	UPROPERTY(BlueprintAssignable)
	FOnAnyStorWriteResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyStorWriteResponse OnError;
};
