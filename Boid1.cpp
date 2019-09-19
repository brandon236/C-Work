#include "Boid1.h"
#include "Boid2.h"
#include "Boid3.h"
#include "Boid4.h"
#include "Boid5.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
ABoid1::ABoid1()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Boid1");

	TimelineRot = CreateDefaultSubobject<UTimelineComponent>("RotationTimeline");


	InterpRotFunction.BindUFunction(this, FName("RotationFloatReturn"));

	// declare trigger capsule
	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	Trigger->InitCapsuleSize(55.f, 96.0f);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = Trigger;

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABoid1::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABoid1::BeginPlay()
{
	Super::BeginPlay();

	alpha = 0.0f;
	Direction = FVector(0.0f, 5.0f, 0.0f);
	AverageDirection = FVector(0.0f, 0.0f, 0.0f);

	Boids.Add(this);
	Boids.Add(Boid2);
	Boids.Add(Boid3);
	Boids.Add(Boid4);
	Boids.Add(Boid5);

	DirectionArray.Add(FVector(0.0f, 0.0f, 0.0f));
	DirectionArray.Add(FVector(0.0f, 0.0f, 0.0f));
	DirectionArray.Add(FVector(0.0f, 0.0f, 0.0f));
	DirectionArray.Add(FVector(0.0f, 0.0f, 0.0f));
	DirectionArray.Add(FVector(0.0f, 0.0f, 0.0f));

	InRange.Add(false);
	InRange.Add(false);
	InRange.Add(false);
	InRange.Add(false);
	InRange.Add(false);

	ObsticleArray.Add(true);
	ObsticleArray.Add(true);
	ObsticleArray.Add(true);
	ObsticleArray.Add(true);
	ObsticleArray.Add(true);
	
	
	if (Curve2) {
		TimelineRot->AddInterpFloat(Curve2, InterpRotFunction, FName("alpha"));

		TimelineRot->SetLooping(false);
		BoidRotation = SetRotation();
	}

}

void ABoid1::OnOverlapBegin(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(FName("Obstacle"))) {
			InRange[0] = false;
			ObstacleArray[0] = false;
			GetWorld->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &ABoid1::ObstacletoTrue, 2.0f, false);
		}
		ChangeDirection();
	}
}

void ABoid1::ObstacletoTrue() {
	ObstacleArray[0] = true;
}

FVector ABoid1::getAverage() {
	return ((GetActorLocation() + (Boid2->GetActorLocation()) + (Boid3->GetActorLocation()) + (Boid4->GetActorLocation()) + (Boid5->GetActorLocation())) / Boids.Num());
}

void ABoid1::ChangeDirection() {
	Direction.X = Direction.X * cos(angle) + Direction.Y * sin(angle);
	Direction.Y = -Direction.X * sin(angle) + Direction.Y * cos(angle);
}


void ABoid1::Move() {
	StartLocation = GetActorLocation();
	EndLocation = Direction;
	alpha += 0.019497f;

	SetActorLocation((StartLocation + Direction), false, 0, ETeleportType::None);

	if (alpha > 2.0f) {
		alpha = 0.0f;
		CenterMass = getAverage();
		Direction = (Normalize(CenterMass - GetActorLocation())) * 15.0f;
		if (Seperation) {
			Direction *= -1;
		}
		BoidRotation = SetRotation();
		TimelineRot->PlayFromStart();
	}
}

FVector ABoid1::Normalize(FVector Point) {
	float v = sqrt(pow(Point.X, 2) + pow(Point.Y, 2) + pow(Point.Z, 2));
	Point.X /= v;
	Point.Y /= v;
	Point.Z /= v;
	return Point;
}


FRotator ABoid1::SetRotation() {
	return (UKismetMathLibrary::MakeRotFromY(Direction));
}


void ABoid1::RotationFloatReturn(float value) {
	SetActorRotation(FMath::Lerp(GetActorRotation(), BoidRotation, value));
}

FVector ABoid1::GetDirection() {
	return Direction;
}

void ABoid1::SetDirection(FVector NewDirection) {
	Direction = NewDirection;
}

void ABoid1::getAverageDirection() {
	AverageDirection = (DirectionArray[0] + DirectionArray[1] + DirectionArray[2] + DirectionArray[3] + DirectionArray[4])/Neighborhood.Num();
	Direction = AverageDirection;
	if (InRange[1]) {
	Boid2 -> SetDirection(AverageDirection);
	}
	if (InRange[2]) {
	Boid3 -> SetDirection(AverageDirection);
	}
	if (InRange[3]) {
	Boid4 -> SetDirection(AverageDirection);
	}
	if (InRange[4]) {
	Boid5 -> SetDirection(AverageDirection);
	}
}

// Called every frame
void ABoid1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

	for (int i = 0; i > Boids.Num(); i++){
		if (i != 0) {
			FVector Distance = GetActorLocation() - (Boids[i] -> GetActorLocation());
			if ((abs(Distance.X) && abs(Distance.Y) && abs(Distance.Z)) < 400.0f) {
				if(ObstacleArray[i]){
					DirectionArray[i] = Boids[i] -> GetDirection();
					Neighborhood.AddUnique(Boids[i]);
					InRange[i] = true;
					getAverageDirection();
				}
			}
		}
	}
}

