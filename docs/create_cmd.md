# Creating a Flank Command

## Example

```
# ${start_year} @description inclusive
# ${end_year} @description exlusive
# $(notes} @capturetab @type textarea

cd /home/ubuntu/repos/data-proc && python my-data-script.py --yearstart ${start_year} --yearend ${end_year} ${ --notes ${notes}
```

This will create a web page for running `my-data-script.py`. It will have input fields labeld `start_year`, `end_year` and `notes`, which will get passed to the Python script. There are various modifications made to each of the inputs. For example, the `notes` field will be a `<textarea>`, not an `<input>`.

## Variable Annotations

| Annotation | Allowed Parameters | Comment |
|------------|--------------------|---------|
| `@colspan` | 1-6 | Determines width of `<input>` |
| `@type` | "textarea" | Changes `<input>` into `<textarea>` |
| `@capturetab` | N/A | Pressing `<TAB>` tabs the cursor in the input, as opposed to jumping to the next input field |
| `@description` | \<string\> | This string goes below the label for an input, like a subtitle of sorts |

