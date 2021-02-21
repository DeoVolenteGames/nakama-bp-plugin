// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaStorageObject.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension|Storage")
struct FNakamaStorageObject {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Collection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	FNakamaStorageObject() {}
	FNakamaStorageObject(NAKAMA_NAMESPACE::NStorageObject Object)
	{
		Collection = FString(Object.collection.c_str());
		Key = FString(Object.key.c_str());
		UserID = FString(Object.userId.c_str());
		Value = FString(Object.value.c_str());
		Version = FString(Object.version.c_str());
	}

	// static TArray<FNakamaStorageObject> MakeArray(const NStorageObjects& Vector)
	// {
	// 	TArray<FNakamaStorageObject> Array;
	// 	Array.SetNumUninitialized(Vector.size());
 //
	// 	for(int i=0; i< Vector.size(); i++){
	// 		Array[i] = Vector[i];
	// 	}
	//
	// 	return Array;
	// }

	// static NStorageObjects& MakeVec(const TArray<FNakamaStorageObject> Array)
	// {
	// 	NStorageObjects& Vector = ;
	// 	Array.SetNumUninitialized(Vector.size());
 //
	// 	for(int i=0; i< Vector.size(); i++){
	// 		Array[i] = Vector[i];
	// 	}
	//
	// 	return Array;
	// }
};
