#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class QueueInterface
{
    public:
        virtual ~QueueInterface(){;}
        virtual void enqueue(int data) = 0;
        virtual int dequeue() = 0;
};


class MockQueue : public QueueInterface
{
    public:
        MOCK_METHOD0(dequeue, int());
        MOCK_METHOD1(enqueue, void(int data));
};


// Comment out after succeded testing
// TEST(GMockTests, CanAssertTrue)
// {
//     ASSERT_TRUE(true);
// }


class DataHolder
{
    public:
        DataHolder(QueueInterface * queue)
        : queue(queue)
        {
            ;
        }
        void addData(int data)
        {
            queue->enqueue(data);
        }
        int getData()
        {
            return queue->dequeue();
        }
    protected:
        QueueInterface * queue;
};


TEST(GMockTests, CanInstantiateDataHolder)
{
    MockQueue mq;
    DataHolder dh(& mq);
}


TEST(GMockTests, CanAddData)
{
    MockQueue mq;
    DataHolder dh(& mq);

    EXPECT_CALL(mq, enqueue(::testing::_));
    dh.addData(1);
}


TEST(GMockTests, CanAddDataAndGetData)
{
    MockQueue mq;
    DataHolder dh(&mq);

    EXPECT_CALL(mq, enqueue(1));
    EXPECT_CALL(mq, dequeue()).WillOnce(::testing::Return(1));

    dh.addData(1);
    auto data = dh.getData();
    ASSERT_EQ(1, data);
}