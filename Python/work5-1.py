import time


def compute():
    x = 0
    for i in range(1000000):
        x = x+i


def average_of_10_times():
    time_start = 0
    time_end = 0
    time_sum = 0
    time_ave = 0
    for i in range(10):
        time_start = time.perf_counter()
        compute()
        time_end = time.perf_counter()
        time_sum = time_end-time_start+time_sum
    time_ave = time_sum/10
    print(time_ave)


if __name__ == '__main__':
    average_of_10_times()
