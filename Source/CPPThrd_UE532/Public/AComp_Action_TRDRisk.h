#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/QueuedThreadPool.h"
#include "Misc/OutputDeviceNULL.h"
#include "Async/AsyncWork.h"
//#include "Math/UnrealMathUtility.h"
#include "AComp_Action_TRDRisk.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTHRD_UE532_API UAComp_Action_TRDRisk : public UActorComponent{
	GENERATED_BODY()

public:	
	UAComp_Action_TRDRisk();

	// destroy test thread
	UFUNCTION(BlueprintCallable, Category = "AComp Action TRDRisk Functions")
		void DestroyThread();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp Action TRDRisk Functions")
		int maxArrayItems = 12;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp Action TRDRisk Functions")
		int areaRange = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp Action TRDRisk Functions")
		int areaSegment = 2;

	UFUNCTION(BlueprintCallable, Category = "AComp Action TRDRisk Functions")
		void SetupItems(int max, float range, FVector shiftLoc, int seg = 2);

	UFUNCTION(BlueprintCallable, Category = "AComp Action TRDRisk Functions")
		void checkTarget(FVector targetLocation = FVector::ZeroVector, float range = 64, FString Command = "");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp Action TRDRisk Functions")
		TArray<AActor*> items;

	UFUNCTION(BlueprintCallable, Category = "AComp Action TRDRisk Functions")
		void setItems(int index, AActor* obj);

	UFUNCTION(BlueprintCallable, Category = "AComp Action TRDRisk Functions")
		TArray<FVector> getLocations();

	TArray<FVector> arrEmplace;
	void makeArray();
	void calibrateEmplace(FVector shiftLoc = FVector::ZeroVector);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool active = true;
	float temp_range = 64.f;
	FVector temp_targetLocation = FVector::OneVector;
	FOutputDeviceNull od;
	float tempF = 0.f;
	FVector tempV = FVector::OneVector;
	AActor* tempA;

		
};



////////////////////////////////////////////////////
////////////////////////////////////////////////////


class TRDAbandonableTaskTest2 : public FNonAbandonableTask {
public:
	// TRDAbandonableTaskTest2 is custom name
	// FNonAbandonableTask is belong to engine 
	// class variables
	float range;
	FVector targetLocation;
	int max;
	FVector arrEmp;
	AActor* itms;
	FOutputDeviceNull od;

public:
	//Default constructor.
	TRDAbandonableTaskTest2(
		float rng,
		FVector loc,
		int mx,
		FVector emp,
		AActor* itm,
		FOutputDeviceNull odn) // set input parameters of class

	{
		// set variable(s) to be used as "parameter" of thread
		this->range = rng;
		this->targetLocation = loc;
		this->max = mx; // maxArrayItems
		this->arrEmp = emp;// arrEmplace
		this->itms = itm; // items
		this->od = odn; //FOutputDeviceNull od;

	}

	// Default destructor
	~TRDAbandonableTaskTest2() {
		//UE_LOG(LogTemp, Warning, TEXT("Task Deleted"));	
	}

	//This function is needed from the API of the engine. So always add this.
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(TRDAbandonableTaskTest, STATGROUP_ThreadPoolAsyncTasks);
	}

	//This function is called when we tell our task to execute... codes here is handle by a new thread
	void DoWork() {
		const FString cmd = FString::Printf(TEXT("Activate %s"), (FVector::Dist(arrEmp, targetLocation) < range) ? TEXT("true") : TEXT("false"));
		if (itms) itms->CallFunctionByNameWithArguments(*cmd, od, NULL, true);
	}
};


