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

### Uncle Bob's 3 Laws of TDD

- You may not write any production code until you have written a failing unit test
- You may not write more of a unit test than is sufficient to fail, and not compiling is failing
- You may not write more production code than is sufficient to pass the currently failing unit test