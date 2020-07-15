# CPP Test Driven Development

## Levels of Testing

- **Unit Testing**: Testing at the function level. This is generally the lowest level of testing and most comprehensive.  
- **Component Testing**: Testing is at the library and compiled binary level testing external interfaces of these components.  
- **System Testing**: Tests the external interfaces of a system which is a collection of sub-systems.  
- **Performance Testing**: Testing done at sub-systems and system levels to verify timing and resource usages are acceptable.  


### Unit Testing Specifics

- Test individual functions
- A test should be written for each test case for a function (all positive and negative test cases)
- Groups of tests can be combined into test suites for better organization
- Executes in the development envionment rather than the production environment
- Execution of the tests should be automated

A simple example:
```cpp
// Production Code
int string_length(std::string theStr)
{
    return theStr.length();
}

// A Unit Test
TEST(StringLengthTests, SimpleTest)
{
    std::string testStr = "1";           // Setup
    int result = string_length("1");     // Action
    ASSERT_EQ(1, result);                // Assert
}
```

Summary:  
- Unit tests are the first safety net for catching bugs before they get to the field
- Unit tests validate test cases for individual functions
- They should build and run in the developer's development environment
- Unit tests should run fast

### Test-Driven Development TDD

- A process where the developer takes personal responsibility for the quality of their code
- Unit tests are written *before* the production code
- Do not write all the tests or production code at once
- Test and production code are both written together in small bits of functionality

TDD Work Flow: Red, Green, Refactor  
- TDD has the following phases in its work flow:
- Write a failing unit test (the RED phase)
- Write just enough production code to make that test pass (the GREEN phase)
- Refactor the unit test and the production code to make it clean (the REFACTOR phase)
- Repeat until the features are complete

RED ==> GREEN ==> REFACTOR (REPEAT)

### Uncle Bob's 3 Laws of TDD

- You may not write any production code until you have written a failing unit test
- You may not write more of a unit test than is sufficient to fail, and not compiling is failing
- You may not write more production code than is sufficient to pass the currently failing unit test

### Google Test Overview

- Goolge Test is an open source C++ unit testing framework from Google
- Provides the ability to create Tests, Test Cases, and Test Suites
- Provides several types of assert macros for generating unit test failures based on boolean, binary and string comparisions
- Has command line parameters to help filter which tests are executed and in what order

**The TEST Macro**

```cpp
TEST(TestCaseName, TestName)
{
    EXPECT_EQ(1, 1);
}
```

- The `TEST` macor defines an individual test for a particular test case
- Tests from the same test cases will be grouped together in the execution output
- Test case and test names should be valid C++ identifiers and shuold not use "_"

**Test Fixtures/Suites**

- Allows for common setup and teardown between tests
- Test Fixtures are classes derived from ::testing::Test
- Each Test Fixture class can implement virtual SetUp and TearDown functions which will be called between each test.
- Tests that are using a test fixture use the `TEST_F` macro rather than `TEST` and pass in the test fixture class name and the test name

```cpp
TEST_F(TEST_F(TestFixtureClass, TestName)))
```

**Test Fixtures - Constructor/Destructor vs SetUp/TearDown**

- Can use test fixtures constructor/destructor instead of SetUp/TearDown since new instance is created for each test
- Constructor/Destructor is preferable as it allows for const member variables and automatic calls to base class constructors
- SetUp/TearDown functions may still be necessary if you may throw an exception during cleanup as this leads to undefined behaviour in destructors

```cpp
class TestFixtureExample : public ::testing::Test
{
    public:
        TestFixtureExample::TestFixtureExample
        {
            testObj = new TestObj();
        }

        virtual void TearDown()
        {
            delete(testObj);
        }

        TEST_F(TestFixtureExample, TestIt)
        {
            ASSERT_TRUE(testObj->run());
        }
}
```

**Google Test Asserts**

- Perform the checks that determine if a test passes or fails
- Two failure types:
    - `ASSERT_*` macros which abourt the current test if they fail
    - `EXPECT_*` macros which indicate a failure but do not abort the current test
- `EXPECT_*` macros should be used if possible
- Four Comparison Types:
    - Basic - Verifies that a passed boolean expression evaluates to true or false
    - Binary - Compares binary values to see if they are equal, not equal, less than, less than or equal, greater than, greater than or equal
    - String - Compares two C style strings to see if they are equal, not equal, equal ignoring case, or not equal ignoring case
    - Floats/Doubles - Compares two floats or doubles to see if they are "close" to equal. Also provides an assert for specifying the max allowed difference between the floats

**Basic Comparison Example**

```cpp
TEST(Examples, BasisAssertExamples)
{
    ASSERT_TRUE(1 == 1);  // Pass
    ASSERT_FALSE(1 == 2);  // Pass
    ASSERT_TRUE(1 == 2);  // Fail
    ASSERT_FALSE(1 == 1);  // Fail
}
```

**Binary Comparison Example**

```cpp
TEST(Examples, BinaryAssertsExampls)
{
    ASSERT_EQ(1, 1);    // Equal
    ASSERT_NE(1, 2);    // Not equal
    ASSERT_LT(1, 2);    // Less than
    ASSERT_LE(1, 1);    // Less than or equal
    ASSERT_GT(2, 1);    // Greater than
    ASSERT_GE(2, 2);    // Greater than or equal to
}
```

**String Comparison Example**

```cpp
TEST(Examples, StringAssertExamples)
{
    ASSERT_EQ(std::string("1"), std::string("1"));
    ASSERT_NE(std::string("a"), std::string("b"));
    ASSERT_STREQ("a", "a");
    ASSERT_STRNE("a", "b");
    ASSERT_STRCASEEQ("A", "a");
    ASSERT_STRCASENE("A", "b");
}
```

**Float/Double Comparison Example**

```cpp
TEST(Examples, FloatDoubleAssertExamples)
{
    ASSERT_FLOAT_EQ(1.0001f, 1.0001f);
    ASSERT_DOUBLE_EQ(1.0001, 1.0001);
    ASSERT_NEAR(1.0001, 1.0001, .0001); // Pass
    ASSERT_NEAR(1.0001, 1.0003, .0001); // Fail
}
```

**Asserts on Exceptions**

- Fails when a specific exception is not thrown, when any exception is not thrown, or when an exception is thrown and none was expected

```cpp
TEST(Examples, ExceptionAssertExamples)
{
    ASSERT_THROW(callIt(), ReallyBadException);
    ASSERT_ANY_THROW(callIt());
    ASSERT_NO_THROW(callIt());  // Pass
}
```


**Command Line Arguments**

- Many command line options available for controlling how tests are run
- gtest_filter: Reular expressions which indicate which tests should be run in the format of `TestCaseRegEx:TestRegEx`
- gtest_repeat: Repeats running the tests for specified number of times. Can be very helpful for ensuring you do not have any flaky test or intermittent failure
- gtest_shuffle: Runs the tests in a randomized order. Helps to ensure no dependencies between the tests (as it should not matter what order the tests are executed)


### Test Doubles

- Almost all code depends (i.e. collaborates) with other parts of the system
- Those other parts of the system are not always easy to replicate in the unit test environment or would make tests slow if used directly
- Test double are objects that are used in unit tests as replacements to the real production system collaborators

**Types of Test Doubles**

- **Dummy**: Objects that can be passed around as necessary but do not have any type of test implementation and should never be used.
- **Fake**: These object generally have a simplified functional implementation of a particular interface that is adequate for testing but not for production
- **Stub**: These objects provide implementations with canned answers that are suitable for the test
- **Spies**: These objects provide implementations that records the values that were passed in sothey can be used by the test
- **Mocks**: These objects are pre-programmed to expect specific calls and parameters and can throw exceptions when necessary

**Dummy Example**

```cpp
class MyDummy : public MyInterface
{
    public:
        void some_function()
        {
            throw "I should not be called!;
        }
};
```

- Dummy objects are expected to never be used and will generally throw an excaption if one of thier methods is actually called.

**Stub Example**

```cpp
class MyStub : public MyInterface
{
    public:
        int some_function()
        {
            return 0;
        }
};
```

- Stubs are different than dummy test doubles in that they do expect to be called and return canned data.

**Fake Example**

```cpp
class MyTestDB : public DBInterface
{
    public:
        void pushData(int data)
        {
            dataItems.push_back(data);
        }
    protected:
        vector<int> dataItems;
};
```

- Fake objecets provide what is usually a simplified implementation of an interface that is functional but not appropriate for production (i.e. an in memory database)

**Spy Example**

```cpp
class MySpy : public MyInterface
{
    public:
        int savedParam;
        void SomeFunction(int param1)
        {
            savedParam = param1;
        }
};
```

- Spy objects save the parameters that were passed into them so they can be analyzed by the test

**Mock Example**

```cpp
class MyMock : public MyInterface
{
    public:
        void some_function(int param1)
        {
            if( 1 != param1)
                throw "I should not be called";
        }
};
```

- Mock objects are the most intelligent test double. they are setup with expectations on how they will be called and will throw exceptions when those expectations are not met.

**Mock Frameworks**

- Most mock frameworks provide easy ways for automatically creating any of these test doubles at runtime
- They provide a fast means for creating mocking expectations for your tests
- They can be much more efficient than implementing custom mock object of your own creation
- Creating mock objects by hand can be tedious and error prone

**Google Mock**

- C++ Mocking Framework from Google
- Included with and works well with Google Test
- Can be used with any C++ Unit Testing Framework

### Google Mock Workflow

- Create Mock Classes derived from the interface classes that the mock is replacing
- In the Mock Class call the MOCK_METHODn Google Mock macro to specify what methods will be mocked
- Create an instance of your mock class in your test
- Then specify the expectations for the test

**Google Mock Expectations**

- Expectations are defined in the test using the EXPECT_CALL macro
- EXPECT_CALL is passed in the mock object and function the expectations is being set for

Example
```cpp
EXPECT_CALL(myMockObj, getData());
```

**Specifying Parameters with Matches**

- For functions that are passed parameters Google Mock needs to know what values are expected.
- This is done with Matchers. Matchers allow you to specify that a parameter is any value, equal to a specific value, or typical mathematical relationships such as gt, lt...

Example
```cpp
EXPECT_CALL(myMockObj, setData(_));
```

**Additional Matcher Examples**
```cpp

EXPECT_CALL(myMockObj, setData(100));
EXPECT_CALL(myMockObj, setData( Ge(100) ));
EXPECT_CALL(myMockObj, setData( NotNull(myObj) ));

```

- You tell Google Mock how many times a function will be called with the `Times` clause
- You can specify an exact number or use a built in expression such as `AtLeast` or `AtMost`

Example
```cpp
EXPECT_CALL(myMockObj, setData(100)),Times(2);
```

**Actions - Telling Goolge Mock What should Happen**

- You tell Google Mockk what should happen when amocked function is called via an Action
- Actions are specified after the Times clause and are things like return values and throwing exceptions
- WillOnce: Specifies an action that will be done on one call to the function
- WillRepeatedly: Specifies an action that is done on many calls to the function

Example
```cpp
EXPECT_CALL(myMockObj, getData()).WillOnce(Return(1));
```

**Additional Action Examples**
```cpp
EXPECT_CALL(myMockObj, getData())
    .WillRepeatedly(Return(1));EXPECT_CALL(myMockObj, getData())
    .WillOnce(Return(1))
    .WillOnce(Return(2))
    .WillOnce(Return(3));

EXPECT_CALL(myMockObj, getData())
    .Times(4)
    .WillRepeatedly(Return(1));
```

### Test Driven Development Best Practices

**Always Do the Next Simplest Test Case**

- Doing the next simplest test case allows you to gradually increase the complexity of your code
- If you jump into the complex test cases too quickly you will find yourself stuck writing a lot of functionality all at once
- Beyond just slowing you down, this can also lead to bad design decisions

**Use Descriptive Test Names**

- Code is read 1000 times more than it is written. Make it clear and readable
- Unit tests are the best ducumentation for how your code works. Make them easy to understand
- Test suites should name the class or function under test and the test names should describe the functionality being tested

**Keep Test Fast**

- One of the biggest benefits of TDD is the fast feedback on how your changes have affected things
- This goes away if your unit tests take more than a few seconds to build and run
- To help your test stay fast try to:
    - Keep console output to a minimum. This slows things down and can clutter up the testing framework output
    - Mock out any slow collaborators with test doubles that are fast

**Use Code Coverage Tools**

- Once you have all your test cases covered and you think you are done run your unit test through a code coverage tool
- This can help you identify any test case you may have missed (i.e. negative test cases)
- You should have a goal of 100% code coverage in functions with real logic them (i.e. not simple getters/setters)

**Run Your Test Multiple Time and In Random Order**

- Running your tests many times will help help ensure that you do not have any flaky test that fail intermittenly
- Running your tests in random order ensures that your tests do not have any dependencies between each other
- Use the gtest_repeat and gtest_shuffle command line parameters with your unit test executable to do this