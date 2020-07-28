#pragma once

#include "main.h"


namespace papyrusMath
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto Abs(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Acos(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Approximately(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a, float b) -> bool;
	auto Asin(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Atan(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Atan2(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float y, float x) -> float;
	auto Ceil(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto CeilToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> std::int32_t;
	auto Clamp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float value, float min, float max) -> float;
	auto Clamp01(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float value) -> float;
	auto ClosestPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::int32_t value) -> std::int32_t;
	auto Cos(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto DeltaAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float current, float target) -> float;
	auto Exp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float p) -> float;
	auto Floor(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto FloorToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_value) -> std::int32_t;
	auto IfThen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, bool value, float t, float f) -> float;
	auto InRange(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float value, float min, float max) -> bool;
	auto InverseLerp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a, float b, float value) -> float;
	auto IsPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::int32_t n) -> bool;
	auto Lerp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a, float b, float t) -> float;
	auto LerpAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a, float b, float t) -> float;
	auto LerpUnclamped(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a, float b, float t) -> float;
	auto Log(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Log10(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Max(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float x, float y) -> float;
	auto Min(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float x, float y) -> float;
	auto MoveTowards(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float current, float target, float maxDelta) -> float;
	auto MoveTowardsAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float current, float target, float maxDelta) -> float;
	auto NextPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::int32_t n) -> std::int32_t;
	auto PingPong(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float t, float length) -> float;
	auto Pow(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f, float p) -> float;
	auto Repeat(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float t, float length) -> float;
	auto Sign(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Round(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto RoundToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> std::int32_t;
	auto Sin(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto SmoothStep(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float from, float to, float t) -> float;
	auto Sqrt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;
	auto Tan(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float f) -> float;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
