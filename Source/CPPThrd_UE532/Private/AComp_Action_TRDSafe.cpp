#include "AComp_Action_TRDSafe.h"

FAsyncTask<TRDAbandonableTaskTest>* Tasker_01; // define thread variable 

UAComp_Action_TRDSafe::UAComp_Action_TRDSafe(){
	PrimaryComponentTick.bCanEverTick = true;

}

void UAComp_Action_TRDSafe::BeginPlay(){
	Super::BeginPlay();
	
}


void UAComp_Action_TRDSafe::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UAComp_Action_TRDSafe::SetupItems(int max, float range, FVector shiftLoc, int seg) {
	maxArrayItems = max;
	areaRange = range;
	areaSegment = seg;
	makeArray();
	calibrateEmplace(shiftLoc);
}

void UAComp_Action_TRDSafe::makeArray() {
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace.Emplace(FMath::VRand());
		//items.Emplace(nullptr);
	}
}

void UAComp_Action_TRDSafe::calibrateEmplace(FVector shiftLoc) {
	int segmentCounter = 1;
	for (int i = 0; i < arrEmplace.Num(); i++) {
		arrEmplace[i] = (arrEmplace[i] * ((areaRange / areaSegment) * segmentCounter)) + shiftLoc;
		if (i > (segmentCounter * maxArrayItems / areaSegment)) segmentCounter++;
	}

}


void UAComp_Action_TRDSafe::checkTarget(FVector targetLocation, float range) {
	(new FAutoDeleteAsyncTask<TRDAbandonableTaskTest>(range, targetLocation, maxArrayItems, arrEmplace, items, od))->StartBackgroundTask();
}

void UAComp_Action_TRDSafe::ActivateItems(FString Command) {
	for (int i = 0; i < items.Num(); i++)
		if (items[i]) items[i]->CallFunctionByNameWithArguments(*Command, od, nullptr, true);
}

TArray<FVector> UAComp_Action_TRDSafe::getLocations() {
	return arrEmplace;
}


void UAComp_Action_TRDSafe::setItems(int index, AActor* obj) {
	items.EmplaceAt(index, obj);
}


///////////////////////////////////

//  ----------- // destroy thread

void UAComp_Action_TRDSafe::DestroyThread() {
	if (Tasker_01) {
		Tasker_01->EnsureCompletion();
		delete Tasker_01;
		Tasker_01 = NULL;
	}
}





