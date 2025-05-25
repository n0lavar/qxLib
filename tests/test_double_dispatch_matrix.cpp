/**

    @file      test_double_dispatch_matrix.cpp
    @author    Khrapov
    @date      25.05.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

#include <qx/containers/string/string.h>
#include <qx/patterns/double_dispatch_matrix.h>
#include <qx/rtti/rtti.h>

#include <numeric>

//V_EXCLUDE_PATH *test_double_dispatch_matrix.cpp

class storage : public qx::rtti_root<>
{
    QX_RTTI_CLASS(storage, qx::rtti_root<>);

public:
    int sum(const storage& other) const;
};

using test_double_dispatch_matrix_type = qx::double_dispatch_matrix<&storage::sum>;

int storage::sum(const storage& other) const
{
    auto&              matrix    = test_double_dispatch_matrix_type::get_instance();
    std::optional<int> optResult = matrix.invoke(*this, other);
    EXPECT_TRUE(optResult);
    return optResult ? *optResult : 0;
}


class storage_string : public storage
{
    QX_RTTI_CLASS(storage_string, storage);

public:
    storage_string(qx::string_view sNumber) : m_sNumber(sNumber)
    {
    }

    const qx::string& get_number() const
    {
        return m_sNumber;
    }

private:
    qx::string m_sNumber;
};

class storage_int : public storage
{
    QX_RTTI_CLASS(storage_int, storage);

public:
    storage_int(int sNumber) : m_nNumber(sNumber)
    {
    }

    int get_number() const
    {
        return m_nNumber;
    }

private:
    int m_nNumber;
};

class storage_vector : public storage
{
    QX_RTTI_CLASS(storage_vector, storage);

public:
    storage_vector(std::vector<int> numbers) : m_Numbers(std::move(numbers))
    {
    }

    std::span<const int> get_number() const
    {
        return m_Numbers;
    }

private:
    std::vector<int> m_Numbers;
};

QX_CALL_BEFORE_MAIN = []()
{
    auto& matrix = test_double_dispatch_matrix_type::get_instance();

    matrix.register_function<storage_string, storage_string>(std::function(
        [](const storage_string& storage_string1, const storage_string& storage_string2)
        {
            return *storage_string1.get_number().to<int>() + *storage_string2.get_number().to<int>();
        }));

    matrix.register_function<storage_string, storage_int>(std::function(
        [](const storage_string& storage_string, const storage_int& storage_int)
        {
            return *storage_string.get_number().to<int>() + storage_int.get_number();
        }));

    matrix.register_function<storage_string, storage_vector>(std::function(
        [](const storage_string& storage_string, const storage_vector& storage_vector)
        {
            return *storage_string.get_number().to<int>()
                   + std::accumulate(storage_vector.get_number().begin(), storage_vector.get_number().end(), 0);
        }));

    matrix.register_function<storage_int, storage_int>(std::function(
        [](const storage_int& storage_int1, const storage_int& storage_int2)
        {
            return storage_int1.get_number() + storage_int2.get_number();
        }));

    matrix.register_function<storage_int, storage_vector>(std::function(
        [](const storage_int& storage_int, const storage_vector& storage_vector)
        {
            return storage_int.get_number()
                   + std::accumulate(storage_vector.get_number().begin(), storage_vector.get_number().end(), 0);
        }));

    matrix.register_function<storage_vector, storage_vector>(std::function(
        [](const storage_vector& storage_vector1, const storage_vector& storage_vector2)
        {
            return std::accumulate(storage_vector1.get_number().begin(), storage_vector1.get_number().end(), 0)
                   + std::accumulate(storage_vector2.get_number().begin(), storage_vector2.get_number().end(), 0);
        }));

    ASSERT_TRUE(matrix.check_matrix_completeness());
};

TEST(double_dispatch_matrix, main)
{
    storage_string storageString10(QX_TEXT("10"));
    storage_int    storageInt10(10);
    storage_vector storageVector10({ 1, 2, 3, 4 });

    storage_string storageString6(QX_TEXT("6"));
    storage_int    storageInt6(6);
    storage_vector storageVector6({ 1, 2, 3 });

    EXPECT_EQ(storageString10.sum(storageString6), 16);
    EXPECT_EQ(storageString10.sum(storageInt6), 16);
    EXPECT_EQ(storageString10.sum(storageVector6), 16);
    EXPECT_EQ(storageInt10.sum(storageInt6), 16);
    EXPECT_EQ(storageInt10.sum(storageVector6), 16);
    EXPECT_EQ(storageVector10.sum(storageVector6), 16);
}
