// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class SPARTA_5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();

protected:
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float range = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<FVector> destinations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<float> distances;

private:
	void EndEvent();
	void CalculateDistanceAndLocation();
	void CreateRandomEvent();

	int32_t Step();
	float timer = 0.f;
	float totalDistance = 0.f;

	int curIndex = 0;
	int eventCallCount = 0;

	bool stop = false;
};
