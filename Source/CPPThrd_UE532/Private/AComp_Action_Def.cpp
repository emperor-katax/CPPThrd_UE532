#include "AComp_Action_Def.h"

UAComp_Action_Def::UAComp_Action_Def(){
	PrimaryComponentTick.bCanEverTick = true;

}


void UAComp_Action_Def::BeginPlay(){
	Super::BeginPlay();


}


void UAComp_Action_Def::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UAComp_Action_Def::SetupItems(int max, float range, FVector shiftLoc, int seg) {
	maxArrayItems = max;
	areaRange = range;
	areaSegment = seg;
	makeArray();
	calibrateEmplace(shiftLoc);
}

void UAComp_Action_Def::makeArray() {
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace.Emplace(FMath::VRand());
		//items.Emplace(nullptr);
	}
}

void UAComp_Action_Def::calibrateEmplace(FVector shiftLoc) {
	int segmentCounter = 1;
	for (int i = 0; i < maxArrayItems; i++) {
		arrEmplace[i] = (arrEmplace[i] * ((areaRange / areaSegment) * segmentCounter)) + shiftLoc;
		if (i > (segmentCounter * maxArrayItems / areaSegment)) segmentCounter++;
	}
}


void UAComp_Action_Def::checkTarget(FVector targetLocation, float range, FString Command) {
	for (int i = 0; i < maxArrayItems; i++) {
		const FString cmd = FString::Printf(TEXT("Activate %s"), ((FVector::Dist(arrEmplace[i], targetLocation)) < range) ? TEXT("true") : TEXT("false"));
		items[i]->CallFunctionByNameWithArguments(*cmd, od, NULL, true);
		items[i]->CallFunctionByNameWithArguments(*Command, od, NULL, true);
	}

}

TArray<FVector> UAComp_Action_Def::getLocations() {
	return arrEmplace;
}


void UAComp_Action_Def::setItems(int index, AActor* obj) {
	items.EmplaceAt(index, obj);
}



