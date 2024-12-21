import csv
import random

# Список фруктов и овощей
fruits_and_vegetables = [
    "Apple", "Banana", "Orange", "Grape", "Mango", "Pineapple", "Strawberry", "Blueberry", 
    "Carrot", "Broccoli", "Spinach", "Potato", "Tomato", "Cucumber", "Lettuce", "Pepper"
]

# Функция для генерации случайных данных
def generate_random_data(num_rows, filename):
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['Number', 'Name', 'Double'])  # Заголовок столбцов
        
        for _ in range(num_rows):
            number = random.randint(1, 100)  # Случайное число
            name = random.choice(fruits_and_vegetables)  # Случайный фрукт или овощ
            double = random.random()
            writer.writerow([number, name, double])

# Генерация файла с 100 строками
generate_random_data(100, 'food.csv')
