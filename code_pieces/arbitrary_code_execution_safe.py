import openai
import os

# Set your OpenAI API key
openai.api_key = os.getenv("OPENAI_API_KEY")  # Use an environment variable for security

class LLMQueryHandler:
    def __init__(self, model="text-davinci-003"):
        self.model = model
        
    def query_llm(self, prompt):
        """Queries the OpenAI API and returns the response from the model."""
        response = openai.Completion.create(
            model=self.model,
            prompt=prompt,
            max_tokens=150,
            n=1,
            stop=None,
            temperature=0.5,
        )
        return response.choices[0].text.strip()

    def validate_response(self, response: str):
        """A simple validation check (does not guarantee safety)."""
        # For demonstration, only allow responses that seem like expressions or True/False.
        if any(response.startswith(keyword) for keyword in ["True", "False", "0", "1", "+", "-", "*", "/", "=="]):
            return True
        return False

def process_input(user_input):
    """Processes user input through the LLM and evaluates its response."""
    llm_handler = LLMQueryHandler()

    # Generate a prompt for the LLM to determine an expression
    prompt = f"Based on the statement '{user_input}', provide a Python expression that evaluates to True or False."
    
    llm_response = llm_handler.query_llm(prompt)
    print(f"LLM Response: {llm_response}")

    # Validate the LLM's response
    if llm_handler.validate_response(llm_response):
        try:
            # Evaluate the safe expression
            result = True if llm_response.startswith("True") else False if llm_response.startswith("False") else None
            print(f"Evaluation result: {result}")
        except Exception as e:
            print(f"Error evaluating expression: {e}")
    else:
        print("Response validation failed. Not executing.")

def main():
    """Main function to interact with the user."""
    print("Advanced LLM Prompt Evaluator")
    
    while True:
        user_input = input("Enter a statement to evaluate (or type 'exit' to quit): ")
        
        if user_input.lower() == 'exit':
            print("Exiting the program.")
            break
        
        # Process and evaluate the user input
        process_input(user_input)

if __name__ == "__main__":
    main()
