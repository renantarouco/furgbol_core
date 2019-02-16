#include <gtest/gtest.h>

#include <data_management/sensor_lib_loader.h>
#include <virtual_sensors/isensor.h>

TEST(DataManagementTestSuite, LoadsCreateSensorFunc) {
    SensorLibLoader loader;
    loader.load_sensor_lib("/home/renan/workspace/cpp/furgbol_ws/furgbol_sensors/lib", "simple_sensor");
    EXPECT_FALSE(loader.sensor_libs.find("simple_sensor") == loader.sensor_libs.end());
}

TEST(DataManagementTestSuite, CreatesSensorInstance) {
    SensorLibLoader loader;
    loader.load_sensor_lib("/home/renan/workspace/cpp/furgbol_ws/furgbol_sensors/lib", "simple_sensor");
    ISensor *sensor = loader.sensor_libs["simple_sensor"].create_sensor();
    EXPECT_FALSE(sensor == nullptr);
}

TEST(DataManagementTestSuite, GetsInputNames) {
    SensorLibLoader loader;
    loader.load_sensor_lib("/home/renan/workspace/cpp/furgbol_ws/furgbol_sensors/lib", "simple_sensor");
    EXPECT_EQ(loader.sensor_libs["simple_sensor"].get_input_names(), "x");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}