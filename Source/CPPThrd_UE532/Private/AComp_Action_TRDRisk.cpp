#include "AComp_Action_TRDRisk.h"

FAsyncTask<TRDAbandonableTaskTest2>* Tasker_02; // define thread variable 

UAComp_Action_TRDRisk::UAComp_Action_TRDRisk(){
	PrimaryComponentTick.bCanEverTick = true;

}


void UAComp_Action_TRDRisk::BeginPlay(){
	Super::BeginPlay();

}

void UAComp_Action_TRDRisk::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UAComp_Action_TRDRisk::SetupItems(int max, float range, FVector shiftLoc, int seg) {
	maxArrayItems = max;
	areaRange = range;
	areaSegment = seg;
	makeArray();
	calibrateEmplace(shiftLoc);
}

void UAComp_Action_TRDRisk::makeArray() {
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace.Emplace(FMath::VRand());
		//items.Emplace(nullptr);
	}
}

void UAComp_Action_TRDRisk::calibrateEmplace(FVector shiftLoc) {
	int segmentCounter = 1;
	for (int i = 0; i < arrEmplace.Num(); i++) {
		arrEmplace[i] = (arrEmplace[i] * ((areaRange / areaSegment) * segmentCounter)) + shiftLoc;
		if (i > (segmentCounter * maxArrayItems / areaSegment)) segmentCounter++;
	}
}

// not good practice .... 
void UAComp_Action_TRDRisk::checkTarget(FVector targetLocation, float range, FString Command) {
	for (int i = 0; i < arrEmplace.Num(); i++) {
		tempV = arrEmplace[i];
		tempA = items[i];
		(new FAutoDeleteAsyncTask<TRDAbandonableTaskTest2>(range, targetLocation, maxArrayItems, tempV, tempA, od))->StartBackgroundTask();
		items[i]->CallFunctionByNameWithArguments(*Command, od, nullptr, true);
	}
}

void UAComp_Action_TRDRisk::setItems(int index, AActor* obj) {
	items.EmplaceAt(index, obj);
}

TArray<FVector> UAComp_Action_TRDRisk::getLocations() {
	return arrEmplace;
}


///////////////////////////////////

//  ----------- // destroy thread

void UAComp_Action_TRDRisk::DestroyThread() {
	if (Tasker_02) {
		Tasker_02->EnsureCompletion();
		delete Tasker_02;
		Tasker_02 = NULL;
		active = true;
	}
}



