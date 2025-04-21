#pragma once

/// <summary>
/// ��������� "����", ����������� ��� ��������� ������������ � ���������� ������������
/// </summary>
template <typename T>
struct Node 
{
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};