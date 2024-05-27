#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "AComp_Action_Def.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTHRD_UE532_API UAComp_Action_Def : public UActorComponent{
	GENERATED_BODY()

public:	
	UAComp_Action_Def();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp ActionDef Functions")
		int maxArrayItems = 12;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp ActionDef Functions")
		int areaRange = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp ActionDef Functions")
		int areaSegment = 2;

	UFUNCTION(BlueprintCallable, Category = "AComp ActionDef Functions")
		void SetupItems(int max, float range, FVector shiftLoc, int seg = 2);

	UFUNCTION(BlueprintCallable, Category = "AComp ActionDef Functions")
		void checkTarget(FVector targetLocation = FVector::ZeroVector, float range = 1, FString Command = "");

	UFUNCTION(BlueprintCallable, Category = "AComp ActionDef Functions")
		TArray<FVector> getLocations();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AComp ActionDef Functions")
		TArray<AActor*> items;

	UFUNCTION(BlueprintCallable, Category = "AComp ActionDef Functions")
		void setItems(int index, AActor* obj);

	TArray<FVector> arrEmplace;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void makeArray();
	void calibrateEmplace(FVector shiftLoc = FVector::ZeroVector);
	FOutputDeviceNull od;
		
};
