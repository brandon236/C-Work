// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineObject.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASplineObject::ASplineObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Camera");

	Timer = CreateDefaultSubobject<UTimelineComponent>("BoidTimeline");

	InterpFunction.BindUFunction(this, FName("TimerFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimerFinished"));

}

// Called when the game starts or when spawned
void ASplineObject::BeginPlay()
{
	Super::BeginPlay();

	mResolution = 50.0f;

	ControlPoints.Add(ControlPoint1->GetActorLocation());
	ControlPoints.Add(ControlPoint2->GetActorLocation());
	ControlPoints.Add(ControlPoint3->GetActorLocation());
	ControlPoints.Add(ControlPoint4->GetActorLocation());

	Point1 = ControlPoints[0];

	scale = 1.0f / mResolution;
	Point2 = EvaluateSpline(scale * Index);

	if (Spline) {
		Timer->AddInterpFloat(Spline, InterpFunction, FName("alpha"));
		Timer->SetTimelineFinishedFunc(TimelineFinished);

		Timer->SetLooping(false);
		Timer->PlayFromStart();
	}

}


FVector ASplineObject::EvaluateSpline(float T) {
	FVector NewPoint;
	NewPoint.X = pow((1 - T), 3) * ControlPoints[0].X + (pow((1 - T), 2) * T) * ControlPoints[1].X + ((1 - T) * pow(T, 2)) * ControlPoints[2].X + pow(T, 3) * ControlPoints[3].X;
	NewPoint.Y = pow((1 - T), 3) * ControlPoints[0].Y + (pow((1 - T), 2) * T) * ControlPoints[1].Y + ((1 - T) * pow(T, 2)) * ControlPoints[2].Y + pow(T, 3) * ControlPoints[3].Y;
	NewPoint.Z = pow((1 - T), 3) * ControlPoints[0].Z + (pow((1 - T), 2) * T) * ControlPoints[1].Z + ((1 - T) * pow(T, 2)) * ControlPoints[2].Z + pow(T, 3) * ControlPoints[3].Z;
	return NewPoint;
}


void ASplineObject::TimerFloatReturn(float value) {
	SetActorLocation(FMath::Lerp(Point1, Point2, value));
	SDirection = GetDirection();
	SetActorRotation(FMath::Lerp(GetActorRotation(), (UKismetMathLibrary::MakeRotFromX(SDirection)), value));
}

FVector ASplineObject::GetDirection() {
	SDirection = Normalize(Point2 - Point1);
	return SDirection;
}

FVector ASplineObject::Normalize(FVector Point) {
	float v = sqrt(pow(Point.X, 2) + pow(Point.Y, 2) + pow(Point.Z, 2));
	Point.X /= v;
	Point.Y /= v;
	Point.Z /= v;
	return Point;
}

void ASplineObject::OnTimerFinished() {
	Index++;
	if (Index < mResolution) {
		Point1 = Point2;
		Point2 = EvaluateSpline(scale * Index);
		Timer->PlayFromStart();
	}

}

// Called every frame
void ASplineObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

