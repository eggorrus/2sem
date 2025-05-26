#include "pch.h"
#include "CppUnitTest.h"
#include "CycleList.h"
#include "kurs.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentsTests
{
    TEST_CLASS(StudentsClassTests)
    {
    public:
        TEST_METHOD(TestDefaultConstructor)
        {
            Students student;

            Assert::AreEqual(string(""), student.getFullName());
            Assert::AreEqual(0, student.getGroupNumber());
            Assert::AreEqual(0.0, student.getScholarshipSize());
            Assert::AreEqual(string(""), student.getAdditionalInfo());

            const int* marks = student.getMarks();
            for (int i = 0; i < marksCount; i++) {
                Assert::AreEqual(0, marks[i]);
            }
        }

        TEST_METHOD(TestParameterizedConstructor)
        {
            int testMarks[] = { 5, 4, 3, 5, 4 };
            Students student("Иванов Иван Иванович", 101, testMarks, 1500.50, "Отличник");

            Assert::AreEqual(string("Иванов Иван Иванович"), student.getFullName());
            Assert::AreEqual(101, student.getGroupNumber());
            Assert::AreEqual(1500.50, student.getScholarshipSize());
            Assert::AreEqual(string("Отличник"), student.getAdditionalInfo());

            const int* marks = student.getMarks();
            for (int i = 0; i < marksCount; i++) {
                Assert::AreEqual(testMarks[i], marks[i]);
            }
        }

        TEST_METHOD(TestSettersAndGetters)
        {
            Students student;

            student.setFullName("Петров Петр Петрович");
            Assert::AreEqual(string("Петров Петр Петрович"), student.getFullName());

            student.setGroupNumber(102);
            Assert::AreEqual(102, student.getGroupNumber());

            int newMarks[] = { 3, 3, 4, 5, 4 };
            student.setMarks(newMarks);
            const int* marks = student.getMarks();
            for (int i = 0; i < marksCount; i++) {
                Assert::AreEqual(newMarks[i], marks[i]);
            }

            student.setScholarshipSize(1200.75);
            Assert::AreEqual(1200.75, student.getScholarshipSize());

            student.setAdditionalInfo("Хорошист");
            Assert::AreEqual(string("Хорошист"), student.getAdditionalInfo());
        }

        TEST_METHOD(TestSetMark)
        {
            Students student;
            student.setMark(0, 5);
            student.setMark(4, 3);

            const int* marks = student.getMarks();
            Assert::AreEqual(5, marks[0]);
            Assert::AreEqual(3, marks[4]);
            Assert::AreEqual(0, marks[1]); 
        }

        TEST_METHOD(TestHasNoTwos)
        {
            int goodMarks[] = { 5, 4, 3, 5, 4 };
            Students goodStudent("Good", 101, goodMarks, 1500, "");
            Assert::IsTrue(goodStudent.hasNoTwos());

            int badMarks[] = { 5, 2, 3, 5, 4 };
            Students badStudent("Bad", 101, badMarks, 1500, "");
            Assert::IsFalse(badStudent.hasNoTwos());
        }

        TEST_METHOD(TestHasMostlyFives)
        {
            int mostlyFives[] = { 5, 5, 4, 5, 3 };
            Students fivesStudent("Fives", 101, mostlyFives, 1500, "");
            Assert::IsTrue(fivesStudent.hasMostlyFives());

            int fewFives[] = { 5, 4, 4, 5, 3 };
            Students fewFivesStudent("FewFives", 101, fewFives, 1500, "");
            Assert::IsFalse(fewFivesStudent.hasMostlyFives());
        }
    };

    TEST_CLASS(CycleListTests)
    {
    public:
        TEST_METHOD(TestAddAndCount)
        {
            CycleList<Students> list;
            Assert::AreEqual(0, list.count());

            int marks1[] = { 5,4,3,5,4 };
            list.add(Students("Студент 1", 101, marks1, 1500, ""));
            Assert::AreEqual(1, list.count());

            int marks2[] = { 3,3,4,5,4 };
            list.add(Students("Студент 2", 102, marks2, 1200, ""));
            Assert::AreEqual(2, list.count());
        }

        TEST_METHOD(TestIndexAccess)
        {
            CycleList<Students> list;
            int marks1[] = { 5,4,3,5,4 };
            list.add(Students("Студент 1", 101, marks1, 1500, ""));

            int marks2[] = { 3,3,4,5,4 };
            list.add(Students("Студент 2", 102, marks2, 1200, ""));

            Assert::AreEqual(string("Студент 1"), list[0].getFullName());
            Assert::AreEqual(string("Студент 2"), list[1].getFullName());
        }

        TEST_METHOD(TestRemoveAt)
        {
            CycleList<Students> list;
            int marks1[] = { 5,4,3,5,4 };
            list.add(Students("Студент 1", 101, marks1, 1500, ""));

            int marks2[] = { 3,3,4,5,4 };
            list.add(Students("Студент 2", 102, marks2, 1200, ""));

            list.removeAt(0);
            Assert::AreEqual(1, list.count());
            Assert::AreEqual(string("Студент 2"), list[0].getFullName());
        }

        TEST_METHOD(TestClear)
        {
            CycleList<Students> list;
            int marks1[] = { 5,4,3,5,4 };
            list.add(Students("Студент 1", 101, marks1, 1500, ""));

            list.clear();
            Assert::AreEqual(0, list.count());
        }
    };

    TEST_CLASS(FunctionalTests)
    {
    public:
        TEST_METHOD(TestCalculateStatistics)
        {
            CycleList<Students> studentFlow;

            int marks1[] = { 5,4,5,5,4 };
            studentFlow.add(Students("Студент 1", 101, marks1, 1500, ""));

            int marks2[] = { 4,4,3,5,4 }; // без двоек
            studentFlow.add(Students("Студент 2", 101, marks2, 1500, ""));
            int marks3[] = { 3,2,3,3,4 }; 
            studentFlow.add(Students("Студент 3", 102, marks3, 1500, ""));

            int group101NoTwos = 0;
            int group101MostlyFives = 0;
            int group102NoTwos = 0;
            int group102MostlyFives = 0;

            for (int i = 0; i < studentFlow.count(); i++) {
                if (studentFlow[i].getGroupNumber() == 101) {
                    if (studentFlow[i].hasNoTwos()) group101NoTwos++;
                    if (studentFlow[i].hasMostlyFives()) group101MostlyFives++;
                }
                else if (studentFlow[i].getGroupNumber() == 102) {
                    if (studentFlow[i].hasNoTwos()) group102NoTwos++;
                    if (studentFlow[i].hasMostlyFives()) group102MostlyFives++;
                }
            }

            Assert::AreEqual(2, group101NoTwos);
            Assert::AreEqual(1, group101MostlyFives);
            Assert::AreEqual(0, group102NoTwos);
            Assert::AreEqual(0, group102MostlyFives);
        }
    };
}