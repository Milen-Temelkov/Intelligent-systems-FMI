import csv


def transform_value(value):
    if value == "y":
        return 1
    elif value == "n":
        return -1
    elif value == "?":
        return 0
    else:
        return value


def calculate_mode(row):
    mode = 0
    for value in row:
        if value not in ["republican", "democrat"]:
            mode += int(value)

    return 1 if mode >= 0 else -1


def write_rows_in_file(file_name, rows):
    try:
        with open(file_name, "w", encoding="utf-8", newline="") as file:
            writer = csv.writer(file)
            writer.writerows(rows)
    except Exception as e:
        print(f"Error while writing to {file_name}: {e}")


def clear_characters_from_file_rows(file_name):
    rows = []
    with open(file_name, "r", encoding="utf-8") as file:
        reader = csv.reader(file)
        for row in reader:
            transformed_row = [transform_value(value) for value in row]

            rows.append(transformed_row)

    return rows


def clear_zeroes_from_file_rows(file_name):
    rows = []
    with open(file_name, "r", encoding="utf-8") as file:
        reader = csv.reader(file)
        for row in reader:
            row_mode = calculate_mode(row)

            transformed_row = [row_mode if value == "0" else value for value in row]

            rows.append(transformed_row)
    return rows


def clear_characters_from_file(src_file_name, dest_file_name):
    cleared_rows = clear_characters_from_file_rows(src_file_name)

    write_rows_in_file(dest_file_name, cleared_rows)


def clear_zeroes_from_file(src_file_name, dest_file_name):

    cleared_rows = clear_zeroes_from_file_rows(src_file_name)

    write_rows_in_file(dest_file_name, cleared_rows)


def prepare_data(src_file_name, variant1_dest_file_name, variant2_dest_file_name):
    clear_characters_from_file(src_file_name, variant1_dest_file_name)
    clear_zeroes_from_file(variant1_dest_file_name, variant2_dest_file_name)


def main():
    abstained_data_variant_dest_file_name = "abstained.data"
    mode_data_variant_dest_file_name = "mode.data"
    source_file_name = "house-votes-84.data"

    prepare_data(
        source_file_name,
        abstained_data_variant_dest_file_name,
        mode_data_variant_dest_file_name,
    )


if __name__ == "__main__":
    main()
