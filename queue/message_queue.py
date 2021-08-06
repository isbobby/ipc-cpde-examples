from multiprocessing import Process, Queue


def calc_square(numbers, q):
    for n in numbers:
        q.put(n * n)


if __name__ == "__main__":
    numbers = [2, 3, 5]
    q = Queue()
    p = Process(target=calc_square, args=(numbers, q))

    p.start()
    p.join()

    while q.empty() is False:
        print(q.get())
