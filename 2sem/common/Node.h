#pragma once

/// <summary>
/// Структура "Узел", необходимая для избежания дублирования в дальнейших лабораторных
/// </summary>
template <typename T>
struct Node 
{
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};