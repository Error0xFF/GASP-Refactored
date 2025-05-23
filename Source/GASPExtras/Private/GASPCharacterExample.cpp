﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPCharacterExample.h"
#include "GameFramework/GameplayCameraComponent.h"

// Sets default values
AGASPCharacterExample::AGASPCharacterExample(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;

	GameplayCamera = CreateDefaultSubobject<UGameplayCameraComponent>(TEXT("GameplayCamera"));	
	GameplayCamera->SetIsReplicated(true);

	if (GetMesh())
	{
		GameplayCamera->SetupAttachment(GetMesh());
		GameplayCamera->SetRelativeLocation(FVector::ZAxisVector * 100.f);
	}
}

void AGASPCharacterExample::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PC = Cast<APlayerController>(NewController))
	{
		GameplayCamera->ActivateCameraForPlayerController(PC);
	}
}

void AGASPCharacterExample::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		GameplayCamera->ActivateCameraForPlayerController(PC);
	}
}

void AGASPCharacterExample::SprintAction(bool bPressed)
{
	if (bPressed)
	{
		SetDesiredGait(EGait::Sprint);
	}
	else
	{
		SetDesiredGait(EGait::Run);
	}
}

void AGASPCharacterExample::WalkAction(bool bPressed)
{
	if (GetGait() != EGait::Walk)
	{
		SetDesiredGait(EGait::Walk);
	}
	else
	{
		SetDesiredGait(EGait::Run);
	}
}

void AGASPCharacterExample::CrouchAction(bool bPressed)
{
	if (GetStanceMode() != StanceTags::Crouching)
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AGASPCharacterExample::JumpAction(bool bPressed)
{
	if (LocomotionAction == LocomotionActionTags::Ragdoll)
	{
		StopRagdolling();
		return;
	}

	if (bPressed && !IsDoingTraversal())
	{
		const FTraversalResult Result = TryTraversalAction();

		if ((Result.bTraversalCheckFailed || Result.bMontageSelectionFailed) && CanJump())
		{
			Jump();
		}
	}
	else
	{
		StopJumping();
	}
}

void AGASPCharacterExample::AimAction(bool bPressed)
{
	if (bPressed)
	{
		SetRotationMode(ERotationMode::Aim);
	}
	else
	{
		SetRotationMode(ERotationMode::OrientToMovement);
	}
}

void AGASPCharacterExample::RagdollAction(bool bPressed)
{
	if (bPressed)
	{
		StartRagdolling();
	}
	else
	{
		StopRagdolling();
	}
}

void AGASPCharacterExample::StrafeAction(bool bPressed)
{
	if (GetRotationMode() != ERotationMode::Strafe)
	{
		SetRotationMode(ERotationMode::Strafe);
	}
	else
	{
		SetRotationMode(ERotationMode::OrientToMovement);
	}
}
