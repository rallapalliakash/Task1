/*
 * generator_gTest.cpp
 *
 *  Created for: GlobalLogic
 *       Author: serhii.denysov
 *
 * Unit tests for Generator class.
 *
 * You may change this file, but it will be restored on Jenkins CI side
 * before each build.
 *
 * Try to figure out the business logic of Generator class by the logic of the
 * unit tests.
 *
 * If you are not familiar with Google Test, please follow the link:
 * https://github.com/google/googletest/blob/master/googletest/docs/primer.md
 *
 */

#include "generator.h"

#include "check.h"

#include "gtest/gtest.h"

#include <limits>
#include <vector>
#include <ctime>
#include <cstdio>

const int N = 5;
int* demo_data = new int[N] {2, 4, 6, 8, 10};

TEST(Generator, sizeof)
{
	typedef struct { int* b; int s; } generator_t;
	EXPECT_EQ(sizeof(generator_t), sizeof(Generator));
}

TEST(Generator, set)
{
    Generator generator;
    generator.set(demo_data, N);

	const int *data = generator.get_data();

    for(int i=0;i<N;i++)
    {
	    EXPECT_EQ(data[i], demo_data[i]);
	}
}

TEST(Generator, setfaith)
{
    Generator generator;
    generator.set(demo_data, N);

    const int *data = generator.get_data();

    EXPECT_NE(data, demo_data);
}

TEST(Generator, bad_init)
{
    Generator generator;

	EXPECT_THROW(generator.set(0, 1), std::logic_error);
}

TEST(Generator, bad_init_len)
{
    Generator generator;

	EXPECT_THROW(generator.set(demo_data, 0), std::logic_error);
	EXPECT_THROW(generator.set(demo_data, std::numeric_limits<unsigned int>::max()), std::logic_error);
}

TEST(Generator , defaults)
{
    Generator *pGen = new Generator;

	EXPECT_EQ(0, pGen ->get_data());
	EXPECT_EQ(0, pGen ->get_count());

	delete pGen;
}

TEST(Generator, copy_ok)
{
    // Hi from Coder!
    Generator* pCoder = new Generator;
	pCoder->set(demo_data, N);

    Generator gene;
    gene = *pCoder;

	EXPECT_NE(gene.get_data(), pCoder->get_data());
	EXPECT_EQ(gene.get_count(), pCoder->get_count());

	for(int i=0;i<gene.get_count();i++) {
        ASSERT_EQ(gene.get_data()[i], pCoder->get_data()[i]);
	}

	delete pCoder;
}

TEST(Generator, count_ok)
{
    Generator gen;

    for(int i=1;i<1500;i+=1)
    {
        gen.generate(i);
        ASSERT_EQ(gen.get_count(), i);
    }

    for(int i=1500; i<1000000; i+=11237)
    {
        gen.generate(i);
        ASSERT_EQ(gen.get_count(), i);
    }
}

TEST(Generator, icheck)
{
    const int n = 100000;
    Generator gen;
    gen.generate(n);

    ASSERT_EQ(gen.get_count(), n);

    for(int i=1; i < n; i++) {
        ASSERT_GT(gen.get_data()[i], i);
    }
}

TEST(Generator, inc_check)
{
    const int n = 300;

    Generator gen;
    gen.generate(n);

    ASSERT_EQ(gen.get_count(), n);

    for(int i=1; i < n; i++) {
        ASSERT_GT(gen.get_data()[i], gen.get_data()[i-1]);
    }
}

TEST(Generator, repeat_check)
{
    const int n = 300;

    Generator gen;
    gen.generate(n);

    ASSERT_EQ(gen.get_count(), n);

    for(int i=1; i < n; i++) {
        for(int j=1; j < n && j != i; j++) {
            ASSERT_NE(gen.get_data()[i], gen.get_data()[j]);
        }
    }
}

TEST(Generator, basic)
{
    Generator gen;
    gen.set(demo_data, N);

	for(int i=0; i < N; i++) {
        ASSERT_TRUE(check(gen.get_data()[i]));
    }
}

void dataTest(int n, bool noRepeat = false) {
    Generator gen;
    gen.generate(n);

    ASSERT_EQ(gen.get_count(), n);

    for(int i=0; i < n; i++) {
        if(i>0 && noRepeat) ASSERT_NE(gen.get_data()[i-1], gen.get_data()[i]);
        // std::cout<<" i : "<<i<<" value : "<<gen.get_data()[i]<<std::endl;
        ASSERT_TRUE(check(gen.get_data()[i]));
    }
}

TEST(Generator, own_small)
{
    dataTest(10, true);
}

TEST(Generator, own_medium)
{
    dataTest(50, true);
}

TEST(Generator, own_large)
{
    dataTest(250, true);
}

TEST(Generator, own_ultimate)
{
    dataTest(100000);
}

int main(int argc, char **argv)
{
  printf("Running main() from generator_gTest.cpp\n");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
