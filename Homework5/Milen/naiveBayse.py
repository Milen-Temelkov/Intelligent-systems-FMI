import csv
import math
import random

import numpy
import pandas

VAR_1_PATH = "abstained.data"
VAR_2_PATH = "mode.data"

ATTRIBUTE_NAMES = [
    "Class Name",
    "handicapped-infants",
    "water-project-cost-sharing",
    "adoption-of-the-budget-resolution",
    "physician-fee-freeze",
    "el-salvador-aid",
    "religious-groups-in-schools",
    "anti-satellite-test-ban",
    "aid-to-nicaraguan-contras",
    "mx-missile",
    "immigration",
    "synfuels-corporation-cutback",
    "education-spending",
    "superfund-right-to-sue",
    "crime",
    "duty-free-exports",
    "export-administration-act-south-africa",
]


def read_records_from_csv(file_path):
    records = []
    with open(file_path, mode="r", newline="", encoding="utf-8") as file:
        reader = csv.reader(file)
        for row in reader:
            records.append(row)

    return records


def prepare_data_sets(records):
    democrats = [record for record in records if record[0] == "democrat"]
    republicans = [record for record in records if record[0] == "republican"]

    random.shuffle(democrats)
    random.shuffle(republicans)

    return democrats, republicans


def separate_train_from_test(democrats, republicans, coeficient=0.8):
    democrats_split_index = int(coeficient * len(democrats))
    republicans_split_index = int(coeficient * len(republicans))

    democrats_train_set = democrats[:democrats_split_index]
    democrats_test_set = democrats[democrats_split_index:]

    republicans_train_set = republicans[:republicans_split_index]
    republicans_test_set = republicans[republicans_split_index:]

    train_set = democrats_train_set + republicans_train_set
    test_set = democrats_test_set + republicans_test_set

    random.shuffle(train_set)
    random.shuffle(test_set)

    return train_set, test_set


def prepare_ten_fold_data(democrats, republicans):
    democrats_folds = numpy.array_split(democrats, 10)
    republicans_folds = numpy.array_split(republicans, 10)

    democrats_folds = list(map(lambda x: x.tolist(), democrats_folds))
    republicans_folds = list(map(lambda x: x.tolist(), republicans_folds))

    combined_folds = []

    for dem_fold, rep_fold in zip(democrats_folds, republicans_folds):
        combined_fold = list(dem_fold) + list(rep_fold)

        combined_folds.append(combined_fold)

    return combined_folds


def prepare_ten_fold_data(voters):
    folds = numpy.array_split(voters, 10)

    folds = list(map(lambda x: x.tolist(), folds))

    return folds


def calculateProbability(
    train_data_frame,
    prob_data_frame,
    class_name,
    row_name,
    row_value,
    total_voters_count,
):
    sum_of_answers = train_data_frame[
        (train_data_frame["Class Name"] == class_name)
        & (train_data_frame[row_name] == row_value)
    ].shape[0]

    prob_data_frame.loc[row_name, row_value] = float(
        sum_of_answers / total_voters_count
    )


def teachModel(
    train_data_frame,
    democrats_probs,
    republican_probs,
    row_names,
    col_names,
    total_democrats,
    total_republicans,
):
    for row_name in row_names:
        for value in col_names:
            calculateProbability(
                train_data_frame,
                democrats_probs,
                "democrat",
                row_name,
                row_value=value,
                total_voters_count=total_democrats,
            )
            calculateProbability(
                train_data_frame,
                republican_probs,
                "republican",
                row_name,
                row_value=value,
                total_voters_count=total_republicans,
            )


def testModel(
    test_data_frame,
    democrats_probs,
    democrat_class_probability,
    republican_probs,
    republican_class_probability,
):
    records_count = test_data_frame.shape[0]
    successful_guesses = 0
    for _, row in test_data_frame.iterrows():

        democrat_probability = evaluate_record(
            row[1:], democrats_probs, democrat_class_probability
        )
        republican_probability = evaluate_record(
            row[1:], republican_probs, republican_class_probability
        )

        if democrat_probability > republican_probability:
            if row["Class Name"] == "democrat":
                successful_guesses += 1
        else:
            if row["Class Name"] == "republican":
                successful_guesses += 1

    return (successful_guesses / records_count) * 100


def evaluate_record(row, probs_data_frame, class_probability):
    probability = class_probability
    for attribute in probs_data_frame.index.to_list():
        probability += math.log(probs_data_frame.loc[attribute, row[attribute]] + 1)

    return probability


def execute_model_test(
    train_data_frame,
    test_data_frame,
    democrats_probs,
    republican_probs,
    row_names,
    col_names,
    DEMOCRATS_COUNT,
    REPUBLICANS_COUNT,
):

    teachModel(
        train_data_frame,
        democrats_probs,
        republican_probs,
        row_names,
        col_names,
        DEMOCRATS_COUNT,
        REPUBLICANS_COUNT,
    )

    train_accuracy = testModel(
        train_data_frame,
        democrats_probs,
        DEMOCRATS_COUNT / (DEMOCRATS_COUNT + REPUBLICANS_COUNT),
        republican_probs,
        REPUBLICANS_COUNT / (DEMOCRATS_COUNT + REPUBLICANS_COUNT),
    )

    test_accuracy = testModel(
        test_data_frame,
        democrats_probs,
        DEMOCRATS_COUNT / (DEMOCRATS_COUNT + REPUBLICANS_COUNT),
        republican_probs,
        REPUBLICANS_COUNT / (DEMOCRATS_COUNT + REPUBLICANS_COUNT),
    )

    return train_accuracy, test_accuracy


def main():

    mode = int(input("Select mode: "))

    file_name = "abstained.data" if mode == 0 else "mode.data"

    democrats, republicans = prepare_data_sets(read_records_from_csv(file_name))

    train_data_set, test_data_set = separate_train_from_test(democrats, republicans)

    train_data_frame = pandas.DataFrame(train_data_set, columns=ATTRIBUTE_NAMES)
    test_data_frame = pandas.DataFrame(test_data_set, columns=ATTRIBUTE_NAMES)

    DEMOCRATS_COUNT = train_data_frame[
        (train_data_frame["Class Name"] == "democrat")
    ].shape[0]

    REPUBLICANS_COUNT = train_data_frame[
        (train_data_frame["Class Name"] == "republican")
    ].shape[0]

    row_names = ATTRIBUTE_NAMES[1:]
    col_names = ["-1", "0", "1"] if mode == 0 else ["-1", "1"]

    democrats_probs = pandas.DataFrame(columns=col_names, index=row_names)
    republican_probs = pandas.DataFrame(columns=col_names, index=row_names)

    train_accuracy, test_accuracy = execute_model_test(
        train_data_frame,
        test_data_frame,
        democrats_probs,
        republican_probs,
        row_names,
        col_names,
        DEMOCRATS_COUNT,
        REPUBLICANS_COUNT,
    )

    print(f"Train Set Accuracy: {train_accuracy} %")
    print(f"Test Set Accuracy: {test_accuracy} %")

    folds = prepare_ten_fold_data(train_data_set)

    for index, fold in enumerate(folds):

        train_folds = [f for i, f in enumerate(folds) if i != index]
        train_data = numpy.concatenate(train_folds)

        train_data_frame = pandas.DataFrame(train_data, columns=ATTRIBUTE_NAMES)
        test_data_frame = pandas.DataFrame(fold, columns=ATTRIBUTE_NAMES)

        DEMOCRATS_COUNT = train_data_frame[
            (train_data_frame["Class Name"] == "democrat")
        ].shape[0]

        REPUBLICANS_COUNT = train_data_frame[
            (train_data_frame["Class Name"] == "republican")
        ].shape[0]

        democrats_probs = pandas.DataFrame(columns=col_names, index=row_names)
        republican_probs = pandas.DataFrame(columns=col_names, index=row_names)

        train_accuracy, test_accuracy = execute_model_test(
            train_data_frame,
            test_data_frame,
            democrats_probs,
            republican_probs,
            row_names,
            col_names,
            DEMOCRATS_COUNT,
            REPUBLICANS_COUNT,
        )

        print(f"Accuracy Fold {index + 1}: {test_accuracy} %")


if __name__ == "__main__":
    main()
