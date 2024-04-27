#include <iostream>
#include <cmath>
#include <ctime>
#include <random>

int rolls = 0;
int greens = 0;
int notGreens = 0;
int postDroughtSuccess = 0;
int postDroughtFail = 0;
bool postDrought = false;
int postDroughtCount = 0;
int money = 0;
int drought = 0;

int interval = 0;
int intervalWithGreen = 0;
int intervalNoGreen = 0;
bool intervalHasGreen = false;

int longestDrought = 0;

void autoCount(int roll)
{
    rolls++;
    interval++;
    if (roll == 38 && !intervalHasGreen)
    {
        intervalWithGreen++;
        intervalHasGreen = true;
    }
    if (interval == 34)
    {
        interval = 0;
        if (!intervalHasGreen)
        {
            intervalNoGreen++;
        }
        intervalHasGreen = false;
    }
    if (!postDrought && roll != 38)
    {
        drought++;
        if (drought > longestDrought)
        {
            longestDrought = drought;
        }
        notGreens++;
        if (drought == 200)
        {
            postDrought = true;
        }
    }
    else if (!postDrought && roll == 38)
    {
        drought = 0;
        greens++;
    }
    else if (postDrought && roll != 38)
    {
        notGreens++;
        money -= 100;
        postDroughtCount++;
        drought++;
        if (drought > longestDrought)
        {
            longestDrought = drought;
        }
        if (postDroughtCount == 234)
        {
            postDroughtFail++;
        }
    }
    else if (postDrought && roll == 38)
    {
        greens++;
        money += 3700;
        postDrought = false;
        postDroughtCount = 0;
        drought = 0;
        postDroughtSuccess++;
    }
}

int main()
{
    std::mt19937 rng(time(0));
    std::uniform_int_distribution<int> dist(1, 38);
    for (int i = 0; i < 100000; i++)
    {
        int roll = dist(rng);
        autoCount(roll);
        std::cout << "Rolls: " << rolls << " money: " << money << std::endl;
    }
    std::cout << "FINAL RESULTS:" << std::endl;
    std::cout << "Rolls: " << rolls << std::endl;
    std::cout << "Greens: " << greens << std::endl;
    std::cout << "Not Greens: " << notGreens << std::endl;
    double probabilityGreen = (double)greens / (double)rolls;
    std::cout << "Green probability: " << probabilityGreen << std::endl;
    std::cout << "Interval with green: " << intervalWithGreen << std::endl;
    std::cout << "Interval no green: " << intervalNoGreen << std::endl;
    double probabilityIntervalGreen = (double)intervalWithGreen / (double)(intervalWithGreen + intervalNoGreen);
    std::cout << "Interval green probability: " << probabilityIntervalGreen << std::endl;
    std::cout << "Longest drought: " << longestDrought << std::endl;
    std::cout << "Post drought fails: " << postDroughtFail << std::endl;
    std::cout << "Post drought successes: " << postDroughtSuccess << std::endl;
    double postDroughtSuccessRate = (double)postDroughtSuccess / (double)(postDroughtFail + postDroughtSuccess);
    std::cout << "Post drought success rate: " << postDroughtSuccessRate << std::endl;
    std::cout << "Money gained/lost: " << money << std::endl;
    return 0;
}
