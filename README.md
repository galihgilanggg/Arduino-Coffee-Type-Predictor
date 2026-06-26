# Coffee Aroma Classification using Binary Logistic Regression

This repository contains the source code and dataset for a laboratory prototype designed to classify the aroma of Arabica and Robusta coffee beans. The system utilizes an Arduino UNO R3, MQ2, and MQ135 gas sensors, and applies a Binary Logistic Regression machine learning algorithm.

## 📌 Project Scope
Please note that this project is developed strictly as a **laboratory-scale prototype** to demonstrate the feasibility of using low-cost gas sensors and embedded machine learning for coffee bean classification.

## 🛠️ Hardware & Technologies Used
* **Microcontroller:** Arduino UNO R3
* **Sensors:** MQ2 & MQ135 Gas Sensors
* **Algorithm:** Binary Logistic Regression
* **Languages:** C++ (Arduino) & Python (Jupyter Notebook)

## 🔄 Workflow & Project Structure
The project is divided into three main stages:

1. **Data Acquisition (`.ino`)**
   The raw gas concentration data (PPM) is extracted from the MQ2 and MQ135 sensors using the Arduino UNO. The script `MQ2_MQ135_export2CSV.ino` handles sensor calibration, data reading, and serial output for data mining.

2. **Data Preprocessing (`.csv`)**
   The raw serial data is collected and formatted into a structured `.csv` file. This dataset is manually cleaned and labeled (`1` for Arabica, `0` for Robusta) to ensure it is ready for the training model, resulting in `dataset_kopi.csv`.

3. **Data Analysis & Modeling (`.ipynb`)**
   The cleaned `.csv` file is processed using Python in a Jupyter Notebook. This step includes exploratory data analysis (EDA), training the Binary Logistic Regression model, evaluating metrics (Confusion Matrix, ROC/AUC), and extracting the feature coefficients to determine the final classification.

## 🚀 How to Run
1. Upload the `.ino` file to your Arduino UNO R3 to start reading sensor data.
2. Capture the serial monitor output and save it as a `.csv` file.
3. Clean the dataset to match the format provided in `dataset_kopi.csv`.
4. Open the Jupyter Notebook (`.ipynb`) and run the cells sequentially to train the model and view the classification analysis.
