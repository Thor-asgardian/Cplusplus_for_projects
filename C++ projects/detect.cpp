#include <iostream>
#include <string>
#include <algorithm>

bool isFakeAccount(const std::string& username, int followers, int following, const std::string& bio) {
    if (std::any_of(username.begin(), username.end(), [](char c) { return !isalnum(c); })) {
        return true;
    }

    if (username.find("user") != std::string::npos || username.find("fake") != std::string::npos) {
        return true;
    }

    // You can adjust these thresholds based on typical ratios for legitimate accounts
    double followersToFollowingRatio = static_cast<double>(followers) / following;
    if (followersToFollowingRatio < 0.1) {
        return true; // Suspiciously low followers-to-following ratio
    }

    // You can add more sophisticated checks based on the content of the bio
    if (bio.find("spam") != std::string::npos || bio.find("fake") != std::string::npos) {
        return true;
    }

    return false;
}

int main() {
    std::cout << "Enter the social media account username: ";
    std::string username;
    std::cin >> username;

    // For simplicity, let's assume the number of followers and following and the bio are known
    int followers, following;
    std::string bio;

    std::cout << "Enter the number of followers: ";
    std::cin >> followers;

    std::cout << "Enter the number of following: ";
    std::cin >> following;

    std::cout << "Enter the bio: ";
    std::cin.ignore(); // To consume the newline character left in the stream
    std::getline(std::cin, bio);

    if (isFakeAccount(username, followers, following, bio)) {
        std::cout << "This social media account may be fake.\n";
    } else {
        std::cout << "This social media account seems legitimate.\n";
    }

    return 0;
}