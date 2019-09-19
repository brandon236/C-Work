// Fill out your copyright notice in the Description page of Project Settings.

#include "Sphere_Main.h"


// Sets default values
ASphere_Main::ASphere_Main()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Gravity");

}

// Called when the game starts or when spawned
void ASphere_Main::BeginPlay()
{
	Super::BeginPlay();
	x0 = GetActorLocation();
	angle = 0.0872665f;
	m1 = 4.0f;
	m2 = 2.0f;
	velocity = FVector(0.0f, 0.0f, 0.0f);
	velocity2 = 0.0f;
	gravity = FVector(0.0f, 0.0f, 3.8f);
	Direction = FVector(1.0f, 0.0f, 1.0f);
	T = 0.0f;
}

// Called every frame
void ASphere_Main::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	T += 6.0f*DeltaTime;

	velocity2 += (2.0/3.0*gravity.Z * (sin(angle)));

	Direction.Z = -1.0f / 3.0f*T*velocity2*(sin(angle)) + x0.Z;

	Direction.X = -1.0f / 3.0f*T*velocity2*(cos(angle)) + x0.X;
		
	sign = velocity2*T / 5.5f;

	SetActorLocation((FVector(Direction.X, GetActorLocation().Y, Direction.Z)));
	SetActorRelativeRotation(FRotator(sign, 0.0f, 0.0f));
}

