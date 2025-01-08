// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerManager.h"
#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	destinations.Push(GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Actor Location: %.1f, %.1f, %.1f"), destinations[0].X, destinations[0].Y, destinations[0].Z);

	for (int i = 0; i < 10; i++)
	{
		FVector destination = destinations[i];
		
		destination.X += Step() * range;
		destination.Y += Step() * range;

		destinations.Push(destination);
	}

	curIndex = 0;
	eventCallCount = 0;
	stop = false;
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (stop) return;
	timer += DeltaTime;
	Move();
}

void AMyActor::Move()
{
	FVector curLocation = FMath::Lerp(destinations[curIndex], destinations[curIndex+1], timer);
	SetActorLocation(curLocation);

	if (timer >= 1.f)
	{
		CalculateDistanceAndLocation();
		CreateRandomEvent();

		if (curIndex < destinations.Num() - 2)
		{
			curIndex++;
			timer = 0.0f;
			
			stop = true;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, 
				FTimerDelegate::CreateLambda([this]()
				{
						stop = false;
				}), 1.0f, false);
		}
		else
		{
			EndEvent();
		}
	}
}

void AMyActor::EndEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Total Distance: %.2f"), totalDistance);

	UE_LOG(LogTemp, Warning, TEXT("Event Call Count: %d"), eventCallCount);

	stop = true;
}

void AMyActor::CalculateDistanceAndLocation()
{
	float distance = (destinations[curIndex + 1] - destinations[curIndex]).Length() / range;

	UE_LOG(LogTemp, Log, TEXT("Distance: %.2f"), distance);

	totalDistance += distance;

	FVector curLocation = GetActorLocation() / range;

	UE_LOG(LogTemp, Log, TEXT("Actor Location: %.1f, %.1f, %.1f"), curLocation.X, curLocation.Y, curLocation.Z);
}

void AMyActor::CreateRandomEvent()
{
	if (Step())
	{
		UE_LOG(LogTemp, Log, TEXT("Event triggered successfully."));
		eventCallCount++;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Event not triggered."));
	}
}

int32_t AMyActor::Step()
{
	return FMath::RandRange(0, 1);
}

