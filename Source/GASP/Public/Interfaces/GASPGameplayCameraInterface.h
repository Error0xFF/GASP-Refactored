﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Types/EnumTypes.h"
#include "Types/TagTypes.h"
#include "GASPGameplayCameraInterface.generated.h"


USTRUCT(BlueprintType)
struct FCameraProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECameraStyle CameraStyle{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECameraMode CameraMode{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag StanceMode{StanceTags::Standing};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EViewMode ViewMode{0};
};

/**
 * 
 */
UINTERFACE()
class UGASPGameplayCameraInterface : public UInterface
{
	GENERATED_BODY()
};

class GASP_API IGASPGameplayCameraInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Camera|Properties")
	FCameraProperties GetCameraProperties();
};

UCLASS(meta = (BlueprintThreadSafe))
class GASP_API UGASPGameplayCameraBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Camera|Helpers")
	static FCameraProperties GetCameraProperties(AActor* CameraActor);
};
